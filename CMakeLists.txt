cmake_minimum_required(VERSION 3.25)
project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test main.cpp SvModuleGenerator.cpp SvModuleGenerator.h FunctionEvaluator.h UsualFunctionEvaluator.h LimitBase.cpp LimitBase.h LimitBase.cpp PointLimit.cpp PointLimit.h InfinityLimit.cpp InfinityLimit.h NumberRounder.cpp NumberRounder.h ExpressionParser/TreeNode.cpp ExpressionParser/TreeNode.h ExpressionParser/Operator.cpp ExpressionParser/Operator.h)
target_include_directories(test PRIVATE ExpressionParser)
