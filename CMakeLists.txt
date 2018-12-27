cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(untitled ConditionCommand.cpp ConnectCommand.cpp CreateCommandMap.cpp Div.cpp IfCommand.cpp main.cpp Minus.cpp Mult.cpp MySocket.cpp Number.cpp OpenDataServerCommand.cpp OrganizedData.cpp Plus.cpp PrintCommand.cpp ShuntingYard.cpp VarCommand.cpp BinaryExpression.h CommandExpression.h Command.h ConditionCommand.h ConnectCommand.h CreateCommandMap.h Div.h Expression.h IfCommand.h Minus.h Mult.h MySocket.h Number.h OpenDataServerCommand.h OrganizedData.h Plus.h PrintCommand.h ShuntingYard.h VarCommand.h WhileCommand.cpp WhileCommand.h Runner.cpp SleepCommand.cpp SleepCommand.h EntercCommand.cpp EntercCommand.h ExitCommand.cpp ExitCommand.h)