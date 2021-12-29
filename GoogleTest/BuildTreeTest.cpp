#include "pch.h"

using namespace std;
using namespace Lex;

class RegexGenerateTreeTest : public ::testing::Test {
protected:
	int id;
	Logger* logger;
	RegexService* regexService;
	RegexGenerateTreeTest()
	{
		logger = new Logger("RegexGenerateTreeTest");
		regexService = new RegexService(*logger);
		id = 0;
	}
	void SetUp() override {
		id = 0;
	}
};

TEST_F(RegexGenerateTreeTest, addBlockAfterIdTest)
{
	string reg = "a[a-b]";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::BLOCK);
	EXPECT_EQ(secondChild->getBlockId(), "a-b");
}

TEST_F(RegexGenerateTreeTest, addBlockAfterOrTest)
{
	string reg = "a|[a-b]";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::BLOCK);
	EXPECT_EQ(secondChild->getBlockId(), "a-b");
}

TEST_F(RegexGenerateTreeTest, addBlockTest)
{
	string reg = "[a-b]|a";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::BLOCK);
	EXPECT_EQ(firstChild->getBlockId(), "a-b");

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addBlockWithVariableTest)
{
	string reg = "[znak]|a";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::BLOCK);
	EXPECT_EQ(firstChild->getBlockId(), "znak");

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addMaximumAndMinimumCharWithMustageBracketsTest)
{
	string reg = "a{2,3}";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	RegexNode* thirdChild = secondChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getFirstChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'a');

	RegexNode* fifthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addMaximumCharWithMustageBracketsTest)
{
	string reg = "a{,2}";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::QUESTION);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	RegexNode* thirdChild = secondChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getFirstChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addMinimumCharWithMustageBracketsTest)
{
	string reg = "a{2,}";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::STAR);

	RegexNode* thirdChild = secondChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getFirstChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'a');

	RegexNode* fifthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addthreeCharWithMustageBracketsTest)
{
	string reg = "a{3}";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'a');
}

TEST_F(RegexGenerateTreeTest, addQuestionTest)
{
	string reg = "a?bc?";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::QUESTION);

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild().get();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild().get();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addBracketsTest)
{
	string reg = "a?(b|c(a|b)|a)a";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	tree = tree->getFirstChild().get();

	firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::QUESTION);

	secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::OR);

	RegexNode* thirdChild = firstChild->getFirstChild().get();

	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* rightTree = tree->getSecondChild().get();

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	rightTree = rightTree->getFirstChild().get();

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::OR);

	RegexNode* leftTree = rightTree->getFirstChild().get();
	rightTree = rightTree->getSecondChild().get();

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'b');

	firstChild = leftTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'b');

	secondChild = leftTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addPlusTest)
{
	string reg = "a+bc+";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::PLUS);

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::PLUS);

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild().get();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild().get();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addStarTest)
{
	string reg = "a*bc*";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::STAR);

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::STAR);

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild().get();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild().get();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addCombineTest)
{
	string reg = "abc";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}

TEST_F(RegexGenerateTreeTest, addOrTest)
{
	string reg = "a|b|c";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}

TEST_F(RegexGenerateTreeTest, BuildTreeTest)
{
	string reg = "a|b*c|(d+e?y{2})*ha";

	RegexNode* tree = regexService->generateTree(reg, id);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);
	EXPECT_EQ(tree->getSecondChild()->getType(), RegexNodeType::END);

	tree = tree->getFirstChild().get();
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	tree = tree->getFirstChild().get();

	firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	secondChild = tree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'h');

	tree = tree->getFirstChild().get();

	firstChild = tree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* leftTree = tree->getFirstChild().get();

	firstChild = leftTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	secondChild = leftTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	leftTree = leftTree->getFirstChild().get();

	firstChild = leftTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	secondChild = leftTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::STAR);

	RegexNode* thirdChild = secondChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'b');

	RegexNode* rightTree = tree->getSecondChild().get();
	EXPECT_EQ(rightTree->getType(), RegexNodeType::STAR);

	rightTree = rightTree->getFirstChild().get();
	EXPECT_EQ(rightTree->getType(), RegexNodeType::COMBINE);

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'y');

	rightTree = rightTree->getFirstChild().get();

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'y');

	rightTree = rightTree->getFirstChild().get();

	firstChild = rightTree->getFirstChild().get();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::PLUS);

	secondChild = rightTree->getSecondChild().get();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	thirdChild = firstChild->getFirstChild().get();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'd');

	RegexNode* fourthChild = secondChild->getFirstChild().get();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'e');
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}