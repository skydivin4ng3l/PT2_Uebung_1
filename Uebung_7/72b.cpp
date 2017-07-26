const int foo1(float test) {
	int quadrat = test *test;
	return quadrat;
}

const float foo2(const float test) {
	test = test / 2.0;
	return test;
}

const float foo3(const float test) {
	return test*2.0;
}

int main(int argc, char** argv){
	float test1 = 2.0;
	test1 = foo1(test1);

	test1 = foo2(test1);

	auto test2 = foo3(test1); //auto kann kein const besitzen!
	test2 += 2.0;
	
	return 0;
}
