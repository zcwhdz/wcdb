/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef Error_hpp
#define Error_hpp

#include <functional>
#include <string>

#ifdef DEBUG

//debug assert
#define WCTAssert(cond, message)                                               \
    if (!(cond)) {                                                             \
        WCDB::Error::fatal(message);                                           \
    }

//remedial assert
#define WCTRemedialAssert(cond, message, remedial) WCTAssert(cond, message)

//remedial fatal error
#define WCTRemedialFatalError(message, remedial) WCDB::Error::fatal(message)

#else //ELSE

#define WCTAssert(cond, message)

//remedial assert
#define WCTRemedialAssert(cond, message, remedial)                             \
    if (!(cond)) {                                                             \
        remedial                                                               \
    }

//remedial fatal error
#define WCTRemedialFatalError(message, remedial)                               \
    do {                                                                       \
        remedial                                                               \
    } while (false);

#endif //DEBUG

#define WCTInnerAssert(cond)                                                   \
    WCTAssert(cond,                                                            \
              "If you think it's a bug caused by WCDB, please report to us.")

namespace WCDB {

class Error {
public:
    Error();

    static constexpr int type = 1;
    virtual int getType() const;

    enum class Level : int {
        Ignore,
        Debug,
        Warning,
        Error,
        Fatal,
    };
    Level level;
    static constexpr const char *LevelName(const Level &level)
    {
        switch (level) {
            case Level::Ignore:
                return "IGNORE";
            case Level::Debug:
                return "DEBUG";
            case Level::Warning:
                return "WARNING";
            case Level::Error:
                return "ERROR";
            case Level::Fatal:
                return "FATAL";
        }
    }

    enum class Code {
        Error = -1,
    };
    int code;
    bool isOK() const;

    std::string message;

    virtual std::string getDescription() const;

    void report();

    class Report {
    public:
        typedef std::function<void(const Error &)> Callback;
        static Report *sharedReport();

        void report(const Error &error);
        void setCallback(const Callback &callback);
        void resetCallback();

    protected:
        Report(const Callback &callback);
        static Callback s_defaultCallback;
        std::shared_ptr<Callback> m_callback;
    };

    static void warning(const std::string &message);
    static void fatal(const std::string &message) __attribute__((noreturn));

protected:
    void addToDescription(std::string &description,
                          const char *key,
                          int64_t value) const;
    void addToDescription(std::string &description,
                          const char *key,
                          const std::string &value) const;
};

} //namespace WCDB

#endif /* Error_hpp */
