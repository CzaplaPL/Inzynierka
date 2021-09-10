#include "pch.h"
#include "../Translator/lekser/regex/RegexService.cpp"
#include "../Translator/lekser/regex/RegexNode.cpp"
#include "../Translator/lekser/regex/RegexNodeType.h"

using namespace std;

TEST(RegexTest, addOrTest)
{
	string reg = "a|b|c";
	RegexService regexServices;

	RegexNode tree = regexServices.generateTree(reg);
	EXPECT_EQ(tree.getType(), RegexNodeType::OR);

	RegexNode* firsChild = tree.getFirstChild();
	EXPECT_EQ(firsChild->getType(), RegexNodeType::OR);

	RegexNode* secondChild = tree.getSecondChild();
	EXPECT_EQ(firsChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firsChild->getValue(), "c");

	RegexNode* thirdChild = firsChild->getFirstChild();
	EXPECT_EQ(thirdChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(thirdChild->getValue(), "a");

	RegexNode* fourthChild = firsChild->getSecondChild();
	EXPECT_EQ(fourthChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(fourthChild->getValue(), "b");
}