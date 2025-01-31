// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>
#include <gtest/gtest.h>
#include "low_precision_transformations/mat_mul_transformation.hpp"

using namespace LayerTestsDefinitions;

namespace {
const std::vector<ov::element::Type> precisions = {
    ov::element::f32,
    ov::element::f16
};

std::vector<MatMulTransformationTestValues> testValues = {
    {
        { 1, 4, 12, 2 },
        { 256ul, ov::Shape({}), {0.f}, {25.5f}, {0.f}, {25.5f} },
        { 1, 4, 2, 12 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} }
    },
    {
        { 1, 4, 12, 2 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} },
        { 1, 4, 2, 12 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} }
    },
    {
        { 1, 1, 1, 4, 12, 2 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} },
        { 1, 1, 1, 4, 2, 12 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} },
    },
    {
        { 12 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} },
        { 12 },
        { 256ul, ov::Shape({}), {-12.8f}, {12.7f}, {-12.8f}, {12.7f} },
    }
};

INSTANTIATE_TEST_SUITE_P(smoke_LPT, MatMulTransformation,
    ::testing::Combine(
        ::testing::ValuesIn(precisions),
        ::testing::Values(ov::PartialShape({ 1, 384, 1024 })),
        ::testing::Values(ov::test::utils::DEVICE_GPU),
        ::testing::ValuesIn(testValues)),
    MatMulTransformation::getTestCaseName);
}  // namespace
