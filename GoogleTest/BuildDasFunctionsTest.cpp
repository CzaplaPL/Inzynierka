#include "pch.h"
#include <vector>
#include "../Translator/lekser/DAS/DasBuilder.h"
class BuildDasFunctionsTest : public ::testing::Test {
protected:
	Logger* logger;
	int id;
	RegexService* regexService;
	DasBuilder* dasBuilder;

	BuildDasFunctionsTest()
	{
		logger = new Logger("BuildDasFunctionsTest");
		regexService = new RegexService(*logger);
		dasBuilder = new DasBuilder(*logger);
		id = 0;
	}

	void SetUp() override {
		id = 0;
	}
};

TEST_F(BuildDasFunctionsTest, testNullableFunction)
{
	string reg = "ab|c";
	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(dasBuilder->nullable(tree));

	reg = "a?";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasBuilder->nullable(tree));

	reg = "a*";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasBuilder->nullable(tree));

	reg = "a*|b";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(!dasBuilder->nullable(tree));

	reg = "(a|b)*abb";
	tree = regexService->generateTree(reg, id);
	EXPECT_FALSE(dasBuilder->nullable(tree));
}

TEST_F(BuildDasFunctionsTest, testFirstPosFunction)
{
	string reg = "ab|c";
	RegexNode* tree = regexService->generateTree(reg, id);
	vector<int> result = dasBuilder->firstPos(tree);
	vector<int> expected = { 0,4 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "a?";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->firstPos(tree);
	expected = { 0 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "a*";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->firstPos(tree);
	expected = { 0 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "a*|b";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->firstPos(tree);
	expected = { 0,3 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "(a|b)*abb";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->firstPos(tree);
	expected = { 0,2,5 };
	EXPECT_EQ(result, expected);
}

TEST_F(BuildDasFunctionsTest, testFollowPosFunction)
{
	string reg = "a(b|c)";
	RegexNode* tree = regexService->generateTree(reg, id);
	vector<int> result = dasBuilder->followPos((*tree)[0]);
	vector<int> expected = { 2,4 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "a?c|d";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->followPos((*tree)[0]);
	expected = { 3 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "ab";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->followPos((*tree)[0]);
	expected = { 2 };
	EXPECT_EQ(result, expected);
	id = 0;
	reg = "(a|b)*abb";
	tree = regexService->generateTree(reg, id);
	result = dasBuilder->followPos((*tree)[0]);
	expected = { 0,2,5 };
	EXPECT_EQ(result, expected);
}

TEST_F(BuildDasFunctionsTest, testGenerateDas)
{
	string reg = "a(b|c)";
	RegexNode* tree = regexService->generateTree(reg, id);
	Das result = dasBuilder->generateDas(tree, "TOKEN");
	int c = 0;
}