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

#ifndef CoreError_hpp
#define CoreError_hpp

#include <WCDB/Abstract.h>
#include <WCDB/Error.hpp>

namespace WCDB {

class CoreError : public HandleError {
public:
    static constexpr int type = 4;

    using HandleError::HandleError;
    using Tag = HandleError::Tag;

    CoreError(const HandleError &);
    CoreError(const Tag &tag, const std::string &message);

    CoreError &operator=(const HandleError &);

    int getType() const override;
};

} //namespace WCDB

#endif /* CoreError_hpp */
