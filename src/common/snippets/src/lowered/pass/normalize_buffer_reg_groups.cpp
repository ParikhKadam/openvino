// Copyright (C) 2023 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "snippets/lowered/pass/normalize_buffer_reg_groups.hpp"

#include "snippets/op/buffer.hpp"
#include "snippets/itt.hpp"


namespace ov {
namespace snippets {
namespace lowered {
namespace pass {

bool NormalizeBufferRegisterGroups::run(lowered::LinearIR& linear_ir, lowered::LinearIR::constExprIt begin, lowered::LinearIR::constExprIt end) {
    OV_ITT_SCOPED_TASK(ov::pass::itt::domains::SnippetsTransform, "Snippets::NormalizeBufferRegisterGroups");

    // [ original Buffer reg group -> normalized ]
    std::map<size_t, size_t> buffer_reg_groups;
    for (auto expr_it = begin; expr_it != end; ++expr_it) {
        const auto& expr = *expr_it;
        const auto op = expr->get_node();
        if (const auto buffer = ov::as_type_ptr<op::Buffer>(op)) {
            const auto group = buffer->get_reg_group();
            if (buffer_reg_groups.count(group) == 0) {
                const auto new_id = buffer_reg_groups.size();
                buffer_reg_groups[group] = new_id;
            }
            buffer->set_reg_group(buffer_reg_groups[group]);
        }
    }
    return buffer_reg_groups.size();
}

} // namespace pass
} // namespace lowered
} // namespace snippets
} // namespace ov
