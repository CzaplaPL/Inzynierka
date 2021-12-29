#include "pch.h"
//#include <vector>
//#include "../Translator/lekser/DAS/DasBuilder.h"
//class BuildDasFunctionsTest : public ::testing::Test {
//protected:
//	Logger* logger;
//	int id;
//	RegexService* regexService;
//	DasBuilder* dasBuilder;
//
//	BuildDasFunctionsTest()
//	{
//		logger = new Logger("BuildDasFunctionsTest");
//		regexService = new RegexService(*logger);
//		dasBuilder = new DasBuilder(*logger);
//		id = 0;
//	}
//
//	void SetUp() override {
//		id = 0;
//	}
//};
//
//TEST_F(BuildDasFunctionsTest, testNullableFunction)
//{
//	string reg = "ab|c";
//	RegexNode* tree = regexService->generateTree(reg, id);
//	EXPECT_FALSE(dasBuilder->nullable(tree));
//
//	reg = "a?";
//	tree = regexService->generateTree(reg, id);
//	EXPECT_FALSE(!dasBuilder->nullable(tree));
//
//	reg = "a*";
//	tree = regexService->generateTree(reg, id);
//	EXPECT_FALSE(!dasBuilder->nullable(tree));
//
//	reg = "a*|b";
//	tree = regexService->generateTree(reg, id);
//	EXPECT_FALSE(!dasBuilder->nullable(tree));
//
//	reg = "(a|b)*abb";
//	tree = regexService->generateTree(reg, id);
//	EXPECT_FALSE(dasBuilder->nullable(tree));
//}
//
//TEST_F(BuildDasFunctionsTest, testFirstPosFunction)
//{
//	string reg = "ab|c";
//	RegexNode* tree = regexService->generateTree(reg, id);
//	vector<int> result = dasBuilder->firstPos(tree);
//	vector<int> expected = { 0,4 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "a?";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->firstPos(tree);
//	expected = { 0,3 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "a*";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->firstPos(tree);
//	expected = { 0,3 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "a*|b";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->firstPos(tree);
//	expected = { 0,3,5 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "(a|b)*abb";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->firstPos(tree);
//	expected = { 0,2,5 };
//	EXPECT_EQ(result, expected);
//}
//
//TEST_F(BuildDasFunctionsTest, testFollowPosFunction)
//{
//	string reg = "a(b|c)";
//	RegexNode* tree = regexService->generateTree(reg, id);
//	vector<int> result = dasBuilder->followPos((*tree)[0]);
//	vector<int> expected = { 2,4 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "a?c|d";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->followPos((*tree)[0]);
//	expected = { 3 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "ab";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->followPos((*tree)[0]);
//	expected = { 2 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "(a|b)*abb";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->followPos((*tree)[0]);
//	expected = { 0,2,5 };
//	EXPECT_EQ(result, expected);
//	id = 0;
//	reg = "a(b|c)d";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->followPos((*tree)[2]);
//	expected = { 6 };
//	EXPECT_EQ(result, expected);
//}
//
//TEST_F(BuildDasFunctionsTest, testGenerateDas)
//{
//	string reg = "a(b|c)";
//	RegexNode* tree = regexService->generateTree(reg, id);
//	Das result = dasBuilder->generateDas(tree, "TOKEN");
//	EXPECT_EQ(result.getToken(), "TOKEN");
//	EXPECT_EQ(result.getStepSize(), 3);
//	string firstStepId = result.getFirstStepId();
//	MachineStep firstStep = result.getStep(firstStepId);
//	string nextStepId = firstStep.getStepIdForString("a");
//	MachineStep nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("b");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//
//	id = 0;
//	reg = "(a|b)*abb";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->generateDas(tree, "TOKEN2");
//	EXPECT_EQ(result.getToken(), "TOKEN2");
//	EXPECT_EQ(result.getStepSize(), 4);
//	firstStepId = result.getFirstStepId();
//	firstStep = result.getStep(firstStepId);
//	nextStepId = firstStep.getStepIdForString("b");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("b");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("b");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//
//	id = 0;
//	reg = "[a-b]|ab";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->generateDas(tree, "TOKEN3");
//	EXPECT_EQ(result.getToken(), "TOKEN3");
//	EXPECT_EQ(result.getStepSize(), 3);
//	firstStepId = result.getFirstStepId();
//	firstStep = result.getStep(firstStepId);
//	nextStepId = firstStep.getStepIdForString("a-b");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("b");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//
//	id = 0;
//	reg = "a{2,}";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->generateDas(tree, "TOKEN4");
//	EXPECT_EQ(result.getToken(), "TOKEN4");
//	EXPECT_EQ(result.getStepSize(), 3);
//	firstStepId = result.getFirstStepId();
//	firstStep = result.getStep(firstStepId);
//	nextStepId = firstStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//	nextStepId = nextStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//
//	id = 0;
//	reg = "a|b*c|(d+e?y{2})*ha";
//	tree = regexService->generateTree(reg, id);
//	result = dasBuilder->generateDas(tree, "TOKEN5");
//	EXPECT_EQ(result.getToken(), "TOKEN5");
//	EXPECT_EQ(result.getStepSize(), 10);
//	firstStepId = result.getFirstStepId();
//	firstStep = result.getStep(firstStepId);
//	nextStepId = firstStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("c");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("h");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//
//	firstStepId = result.getFirstStepId();
//	firstStep = result.getStep(firstStepId);
//	nextStepId = firstStep.getStepIdForString("d");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("e");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("y");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("y");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("h");
//	nextStep = result.getStep(nextStepId);
//	nextStepId = nextStep.getStepIdForString("a");
//	nextStep = result.getStep(nextStepId);
//	EXPECT_TRUE(nextStep.stepIsAccepting());
//}