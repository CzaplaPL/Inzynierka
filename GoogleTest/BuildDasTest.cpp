#include "pch.h"
//#include <vector>
//#include "../Translator/lekser/DAS/DasBuilder.h"
//#include "../Translator/lekser/DAS/DasService.h"
//class BuildDasTest : public ::testing::Test {
//protected:
//	Logger* logger;
//	int id;
//	RegexService* regexService;
//	DasBuilder* dasBuilder;
//	DasService* dasService;
//
//	BuildDasTest()
//	{
//		logger = new Logger("BuildDasTest");
//		regexService = new RegexService(*logger);
//		dasBuilder = new DasBuilder(*logger);
//		dasService = new DasService(*logger);
//		id = 0;
//	}
//
//	void SetUp() override {
//		id = 0;
//	}
//};
//
//TEST_F(BuildDasTest, test_merge_das_function)
//{
//	string reg = "a";
//	RegexNode* tree = regexService->generateTree(reg, id);
//	Das das1 = dasBuilder->generateDas(tree, "a");
//
//	reg = "abb";
//	tree = regexService->generateTree(reg, id);
//	Das das2 = dasBuilder->generateDas(tree, "abb");
//
//	reg = "a*b";
//	tree = regexService->generateTree(reg, id);
//	Das das3 = dasBuilder->generateDas(tree, "a*b");
//
//	vector<Das> dases;
//	dases.push_back(das1);
//	dases.push_back(das2);
//	dases.push_back(das3);
//
//	Das result = dasService->mergeDases(dases);
//	EXPECT_EQ(result.getStepSize(), 6);
//
//	string firstStepId = result.getFirstStepId();
//	MachineStep stepA = result.getStep(firstStepId);
//
//	EXPECT_FALSE(stepA.stepIsAccepting());
//
//	string nextStepIdForA = stepA.getStepIdForString("a");
//	MachineStep stepB = result.getStep(nextStepIdForA);
//	EXPECT_TRUE(stepB.stepIsAccepting());
//	EXPECT_EQ(stepB.getAcceptingToken(), "a");
//
//	string nextStepIdForB = stepA.getStepIdForString("b");
//	string StepIdForC = nextStepIdForB;
//	MachineStep stepC = result.getStep(nextStepIdForB);
//	EXPECT_TRUE(stepC.stepIsAccepting());
//	EXPECT_EQ(stepC.getAcceptingToken(), "a*b");
//
//	nextStepIdForA = stepB.getStepIdForString("a");
//	MachineStep stepD = result.getStep(nextStepIdForA);
//	EXPECT_FALSE(stepD.stepIsAccepting());
//
//	string nextStepId = stepD.getStepIdForString("a");
//	EXPECT_EQ(nextStepId, nextStepIdForA);
//	nextStepId = stepD.getStepIdForString("b");
//	EXPECT_EQ(nextStepId, StepIdForC);
//
//	nextStepIdForB = stepB.getStepIdForString("b");
//	MachineStep stepE = result.getStep(nextStepIdForB);
//	EXPECT_TRUE(stepE.stepIsAccepting());
//	EXPECT_EQ(stepE.getAcceptingToken(), "a*b");
//
//	EXPECT_THROW(stepE.getStepIdForString("a"); , NoStepException);
//
//	nextStepIdForB = stepE.getStepIdForString("b");
//	MachineStep stepF = result.getStep(nextStepIdForB);
//	EXPECT_TRUE(stepF.stepIsAccepting());
//	EXPECT_EQ(stepF.getAcceptingToken(), "abb");
//
//	EXPECT_THROW(stepF.getStepIdForString("a");, NoStepException);
//	EXPECT_THROW(stepF.getStepIdForString("b");, NoStepException);
//}