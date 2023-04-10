
//#define private public

#include"gtest.h"
#include"../include/PARSER.h"


TEST(mono, can_add_monoms)
{
	mono M;
	mono M2;
	mono M3;
	mono M4;
	int i = 0;
	string s = "2x^2y^2z^2";
	string s2 = "4x^2y^2z^2";
	string s3 = "6x^2y^2z^2";
	M.GetMono(s,&i);
	i = 0;
	M2.GetMono(s2,&i);
	i = 0;
	M3.GetMono(s3, &i);
	M4 = M + M2;
	ASSERT_EQ(M3==M4,true);
}

TEST(mono, can_mult_monoms)
{
	mono M;
	mono M2;
	mono M3;
	mono M4;
	int i = 0;
	string s = "2x^2y^2z^2";
	string s2 = "4x^2y^2z^2";
	string s3 = "8x^4y^4z^4";
	M.GetMono(s, &i);
	i = 0;
	M2.GetMono(s2, &i);
	i = 0;
	M3.GetMono(s3, &i);
	M4 = M * M2;
	ASSERT_EQ(M3 == M4, true);
}

TEST(mono, can_sub_monoms)
{
	mono M;
	mono M2;
	mono M3;
	mono M4;
	int i = 0;
	string s = "2x^2y^2z^2";
	string s2 = "4x^2y^2z^2";
	string s3 = "-2x^2y^2z^2";
	M.GetMono(s, &i);
	i = 0;
	M2.GetMono(s2, &i);
	i = 0;
	M3.GetMono(s3, &i);
	M4 = M - M2;
	ASSERT_EQ(M3 == M4, true);
}

TEST(mono, can_calculate_monoms)
{
	mono M;
	string s = "2x^2y^2z^2";
	int i = 0;
	M.GetMono(s,&i);
	ASSERT_EQ(M.calc(1, 1, 1), 2.0);
}

TEST(mono, can_compare_monoms)
{
	/*
	!!ATTENTION!!
	only degrees (not koeff) has been compared
	it works only with class mono
	*/
	mono M;
	mono M2;
	int i = 0;
	string s = "2x^2y^2z^2";
	string s2 = "2x^3y^2z^2";
	M.GetMono(s, &i);
	i = 0;
	M2.GetMono(s2, &i);
	ASSERT_FALSE(M == M2);
}

TEST(poly, can_add_polynoms)
{
	string str = "pola=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	string str2 = "polb=3x^3y^3z^3";
	string tested = "pol=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3+3x^3y^3z^3";
	poly P;
	poly P2;
	poly TESTED;
	TESTED.GetPoly(tested);
	P.GetPoly(str);
	P2.GetPoly(str2);
	poly P3;
	P3 = P + P2;
	//ASSERT_EQ(P + P2, TESTED);  // да почему оно так не работает(((   вообще нигде так не работает в тестах((
	ASSERT_TRUE(P3==TESTED);
}

TEST(poly, can_sub_polynoms)
{
	string str = "pola=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	string str2 = "polb=3x^3y^3z^3";
	string tested = "pol=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3-3x^3y^3z^3";
	poly P;
	poly P2;
	poly TESTED;
	TESTED.GetPoly(tested);
	P.GetPoly(str);
	P2.GetPoly(str2);
	poly P3;
	P3 = P - P2;
	ASSERT_TRUE(P3 == TESTED);
}

TEST(poly, can_eq_polynoms)
{
	string str = "pola=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	string str2 = "polb=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	poly P;
	poly P2;
	P.GetPoly(str);
	P2.GetPoly(str2);
	ASSERT_TRUE(P==P2);
}

TEST(poly, can_parse_without_deg)
{
	string str = "pola=xy+x-y";
	poly P;
	P.GetPoly(str);
	string str2 = "1x^1y^1+1x^1-y^1";
	poly P2;
	P2.GetPoly(str2);
	ASSERT_TRUE(P == P2);
}

TEST(poly, can_parse_double_num)
{
	string str = "pola=3.1415xy";
	poly P;
	P.GetPoly(str);
	list<mono> L = P.GetValue();
	mono M = *(L.begin());
	double D = M.koef();
	ASSERT_DOUBLE_EQ(D, 3.1415);
}

TEST(poly, can_mult_polynoms)
{
	poly M;
	poly M2;
	poly M3;
	poly M4;
	string s = "2x^2y^2z^2";
	string s2 = "4x^2y^2z^2";
	string s3 = "8x^4y^4z^4";
	M.GetPoly(s);
	M2.GetPoly(s2);
	M3.GetPoly(s3);
	M4 = M * M2;
	ASSERT_EQ(M3 == M4, true);
}

TEST(poly, can_calculate_polynoms)
{
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	EXPECT_DOUBLE_EQ(P.calc(1, 1, 1), 3.0);
}

TEST(poly, can_bring_simular)
{
	string str = "p=7x^2y^2z^2-xy+x-y-z-x+x";
	poly P;
	P.GetPoly(str);
	string out = "s=7x^2y^2z^2-xy+x-y-z";
	poly OUT;
	OUT.GetPoly(out);
	EXPECT_TRUE(OUT == P);
}

//--------------------------------------------------------------------------------------

TEST(table, can_add_element)
{
	table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}

TEST(table, can_delete_element)
{
	table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly PN;
	poly P;
	P.GetPoly(str2);
	T.add(P);
	T.del(P.GetName());
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_FALSE(P2 == P);
}

TEST(table, can_search_element)
{
	table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}

TEST(table, can_get_element)
{
	table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T[0];
	ASSERT_TRUE(P2 == P);
}

//-------------------------------------------------------------------------

TEST(table_list, can_add_element)
{
	table_list<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}

TEST(table_list, can_del_element)
{
	table_list<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	T.del(P.GetName());
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_FALSE(P2 == P);
}

TEST(table_list, can_search_element)
{
	table_list<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}

//--------------------------------------------------------------------------------

TEST(AVLTree, can_add_element)
{
	AVLTree<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}


TEST(AVLTree, can_search_element)
{
	AVLTree<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}

//---------------------------------------------------------------------------------

TEST(ordered_table, can_add_element)
{
	ordered_table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}


TEST(ordered_table, can_delete_element)
{
	ordered_table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	T.del(P.GetName());
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_FALSE(P2 == P);
}

TEST(ordered_table, can_search_element)
{
	ordered_table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T.search(P.GetName());
	ASSERT_TRUE(P2 == P);
}

TEST(ordered_table, can_get_element)
{
	ordered_table<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	poly P2;
	P2 = T[0];
	ASSERT_TRUE(P2 == P);
}

//----------------------------------------------------------------------------------

TEST(chain_hash, can_add_element)
{
	chain_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}

TEST(chain_hash, can_del_element)
{
	chain_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	T.del(P);
	ASSERT_FALSE(T.search(P));
}

TEST(chain_hash, can_search_monoms)
{
	chain_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}

//-----------------------------------------------------------------------------------

TEST(open_adress_hash, can_add_element)
{
	open_adress_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}

TEST(open_adress_hash, can_del_element)
{
	open_adress_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	T.del(P);
	ASSERT_FALSE(T.search(P));
}

TEST(open_adress_hash, can_search_monoms)
{
	open_adress_hash<poly> T;
	string str2 = "polb=3x^3y^3z^3";
	poly P;
	P.GetPoly(str2);
	T.add(P);
	ASSERT_TRUE(T.search(P));
}

//-------------------------------------------------------------------------------------

TEST(EXPRESSION, can_calculate_polynoms)
{
	string str = "pola=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	string str2 = "polb=3x^3y^3z^3";
	string hh = "2*pola+polb+15*10";
	string out = "polPN=-24x^2y^3+4x^2y^2z^2+-4x^2y^2z^3+3x^3y^3z^3+150";
	poly P2;
	poly P;
	poly PN;
	poly POUT;
	PN.GetPoly(out);
	P.GetPoly(str);
	P2.GetPoly(str2);
	table<poly> TABLE;
	TABLE.add(P);
	TABLE.add(P2);
	EXPRESSION<table<poly>> EXPR(hh);
	EXPR.convert();
	POUT=EXPR.calc(TABLE);
	ASSERT_TRUE(POUT == PN);
}

TEST(EXPRESSION, can_calculate_constants)
{
	string hh = "10 * 15 + 278";
	string ans = "428";
	table<poly> TABLE;
	EXPRESSION<table<poly>> EXPR(hh);
	poly P;
	poly P2;
	P.GetPoly(ans);
	EXPR.convert();
	P2 = EXPR.calc(TABLE);
	ASSERT_TRUE(P2 == P);
}

TEST(EXPRESSION, can_convert_to_postfix)
{
	string str = "pola=-12x^2y^3+2x^2y^2z^2-2x^2y^2z^3";
	string str2 = "polb=3x^3y^3z^3";
	string hh = "2*pola+polb+10*15";
	string out = "2 pola *polb +10 15 *+";
	poly P2;
	poly P;
	P.GetPoly(str);
	P2.GetPoly(str2);
	table<poly> TABLE;
	TABLE.add(P);
	TABLE.add(P2);
	EXPRESSION<table<poly>> EXPR(hh);
	EXPR.convert();
	ASSERT_EQ(EXPR.GetPostfix(), out);
}

//---------------------------------------------------------

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}