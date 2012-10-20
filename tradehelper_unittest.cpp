#include "stdafx.h"

#include "ParserXml.h"
//#include "ConnectorNew.h"
#include "SimpleBrowser.h"

TEST(ParserXml, TestParserXml) {
	//EXPECT_FALSE(ParserXml::get_mutable_instance().createSignalCharStrings(new char[]("")));
	EXPECT_TRUE(ParserXml::get_mutable_instance().getSignalCount() == 0);
}