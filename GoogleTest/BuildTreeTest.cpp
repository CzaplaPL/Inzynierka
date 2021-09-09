#include "pch.h"
#include "../Translator/lekser/regex/RegexServices.cpp"
#include "../Translator/lekser/regex/RegexNode.cpp"
#include "../Translator/lekser/regex/RegexNodeType.h"


using namespace std;

TEST(RegexTest, addOrTest)
{
	string reg = "a|b|c";
	RegexServices regexServices;
	RegexNode tree = regexServices.generateTree(reg);

	EXPECT_EQ(tree.getType(), RegexNodeType::OR);
	RegexNode* firsChild = tree.getFirstChild();
}