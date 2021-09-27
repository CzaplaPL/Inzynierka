#include "pch.h"

class BuildDasTest : public ::testing::Test {
protected:
	Logger* logger;
	RegexService* regexService;
	void SetUp() override {
		logger = new Logger("BuildDasTest");
		regexService = new RegexService(*logger);
	}
};

TEST_F(BuildDasTest, dsadaf)
{
	string reg = "a[a-b]";

	RegexNode* tree = regexService->generateTree(reg);
	EXPECT_EQ(tree->getType(), RegexNodeType::COMBINE);

	RegexNode* firstChild = tree->getFirstChild();
	EXPECT_EQ(firstChild->getType(), RegexNodeType::ID);
	EXPECT_EQ(firstChild->getValue(), 'a');

	RegexNode* secondChild = tree->getSecondChild();
	EXPECT_EQ(secondChild->getType(), RegexNodeType::BLOCK);
	EXPECT_EQ(secondChild->getBlockId(), "a-b");
}