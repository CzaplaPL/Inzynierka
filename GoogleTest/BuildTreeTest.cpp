#include "pch.h"

#include "../Translator/addons/Logger.cpp"
#include "../Translator/lekser/regex/RegexNode.cpp"
#include "../Translator/lekser/regex/RegexNodeType.h"
#include "../Translator/lekser/regex/RegexService.cpp"
#include "../Translator/lekser/regex/PreviewElement.cpp"
#include "../Translator/lekser/regex/RegexConstructorSyntaxTree.cpp"

using namespace std;

class RegexTest : public ::testing::Test {
protected:
	Logger* logger;
	RegexService* regexService;
	void SetUp() override {
		logger = new Logger("test");
		regexService = new RegexService(*logger);
	}
};

TEST_F(RegexTest, addCombineTest)
{
	string reg = "abc";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firsChild = tree->getFirstChild();
	EXPECT_EQ(firsChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firsChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firsChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}
TEST_F(RegexTest, addOrTest)
{
	string reg = "a|b|c";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firsChild = tree->getFirstChild();
	EXPECT_EQ(firsChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firsChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firsChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}

TEST_F(RegexTest, BuildTreeTest)
{
	string reg = "a|bc";
	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

³	³	RegexNode* firsChild = tree->getFirstChild();
	EXPECT_EQ(firsChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firsChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firsChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}