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

TEST_F(RegexTest, addstarTest)
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
TEST_F(RegexTest, addCombineTest)
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

TEST_F(RegexTest, addOrTest)
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

TEST_F(RegexTest, BuildTreeTest)
{
	string reg = "a|b*c";
	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(secondChild->getValue(), 'c');

	RegexNode* thirdChild = firstChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), 'a');

	RegexNode* fourthChild = firstChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::STAR);

	RegexNode* fifthChild = fourthChild->getFirstChild();
	EXPECT_EQ(fifthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fifthChild->getValue(), 'b');
}