#include "pch.h"

#include "../Translator/addons/Logger.cpp"
#include "../Translator/lekser/regex/RegexNode.cpp"
#include "../Translator/lekser/regex/RegexNodeType.h"
#include "../Translator/lekser/regex/RegexService.cpp"
#include "../Translator/lekser/regex/PreviewElement.cpp"
#include "../Translator/lekser/regex/RegexConstructorSyntaxTree.cpp"

using namespace std;

class RegexGenerateTreeTest : public ::testing::Test {
protected:
	Logger* logger;
	RegexService* regexService;
	void SetUp() override {
		logger = new Logger("test");
		regexService = new RegexService(*logger);
	}
};

TEST_F(RegexGenerateTreeTest, addBracketsTest)
{
	string reg = "a?(b|c(a|b)|a)a";

	RegexNode* tree = regexService->generateTree(reg);

	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	tree = tree->getFirstChild();

	firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::QUESTION);

	secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::OR);

	RegexNode* thirdChild = firstChild->getFirstChild();

	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* rightTree = tree->getSecondChild();

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	rightTree = rightTree->getFirstChild();

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::OR);

	RegexNode* leftTree = rightTree->getFirstChild();
	rightTree = rightTree->getSecondChild();

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'b');

	firstChild = leftTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'b');

	secondChild = leftTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addQuestionTest)
{
	string reg = "a?bc?";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::QUESTION);

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addPlusTest)
{
	string reg = "a+bc+";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::PLUS);

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::PLUS);

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addStarTest)
{
	string reg = "a*bc*";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::STAR);

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::STAR);

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');

	RegexNode* fifthChild = thirdChild->getFirstChild();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'a');

	RegexNode* sixthChild = secondChild->getFirstChild();
	EXPECT_EQ(sixthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(sixthChild->getValue(), 'c');
}

TEST_F(RegexGenerateTreeTest, addCombineTest)
{
	string reg = "abc";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}

TEST_F(RegexGenerateTreeTest, addOrTest)
{
	string reg = "a|b|c";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::OR);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'b');
}

TEST_F(RegexGenerateTreeTest, BuildTreeTest)
{
	string reg = "a|b*c|(d+e?y{2})*ha";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'a');

	tree = firstChild->getFirstChild();

	firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::STAR);

	secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'h');

	tree = firstChild->getFirstChild();

	firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	tree = firstChild->getFirstChild();

	RegexNode* leftTree = tree->getFirstChild();

	EXPECT_EQ(leftTree->getType(), RegexNodeType::COMBINE);

	firstChild = leftTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	secondChild = leftTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	leftTree = firstChild->getFirstChild();

	firstChild = leftTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	secondChild = leftTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::STAR);

	firstChild = secondChild->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'b');

	RegexNode* rightTree = tree->getSecondChild();

	EXPECT_EQ(rightTree->getType(), RegexNodeType::COMBINE);

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'y');

	rightTree = firstChild->getFirstChild();

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::COMBINE);

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'y');

	rightTree = firstChild->getFirstChild();

	firstChild = rightTree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::PLUS);

	secondChild = rightTree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::QUESTION);

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'd');

	RegexNode* fourthChild = secondChild->getFirstChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), 'e');
}