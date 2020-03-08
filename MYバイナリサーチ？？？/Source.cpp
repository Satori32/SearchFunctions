#include <iostream>
#include <vector>
#include <cstdint>

//https://ideone.com/7O4Dl5

typedef std::vector<std::intmax_t> DType;

DType MakeVector(std::size_t N) {
	DType R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(i);
	}
	return R;
}
template<class T,class Container>
std::size_t BinarySearchBlock(const Container& D, const T& V,std::size_t Div) {//need sorted.
	std::size_t Min = 0;
	std::size_t Max = Div;
	std::size_t H = 0;
	double S = D.size() / (double)Div;
	std::size_t B = H + 0xdeadbeefbd;

	while (((Min-Max) != 0)&&H!=B) {
		B = H;
		H = (Min + Max) / 2;
		if (D[H*S] < V) {
			Min = H;
		}
		else {
			Max = H;
		}
	}

	return H;
}
template<class T,class Container>
std::size_t BinarySearch(const Container& D, const T& V) {//need sorted.
	std::size_t Min = 0;
	std::size_t Max = D.size();
	std::size_t H = Max/2;

	while (((Min-Max) != 0)&& (D[H]!=V)) {
		H = (Min + Max) / 2;
		if (D[H] < V) {
			Min = H;
		}
		else {
			Max = H;
		}
	}

	return H;
}
template<class T,class Container>
std::size_t BlockSearch(const Container& D, const T& V,std::size_t Div) {//need sorted.
	if (D.size() == 0) { return D.size(); }
	double S = (D.size()-1) / (double)Div;
	std::size_t i = 0;
	for(i=1;i<Div;i++){
		if (D[(std::size_t)(i * S)] >= V) {
			break;
		}
	}
	double L = i * S;
	for(std::size_t j=(i-1)*S;j<=L;j++){
		if (D[j] == V) {
			return j ;
		}
	}	
	return D.size();
}
template<class T,class Container>
std::size_t BlockSearchBlock(const Container& D, const T& V,std::size_t Div) {//need sorted.
	if (D.size() == 0) { return D.size(); }
	double S = (D.size()-1) / (double)Div;
	std::size_t i = 0;
	for(i=1;i<Div;i++){
		if (D[(std::size_t)(i * S)] >= V) {
			break;
		}
	}
	return i;
}
template<class it, class T>
it BinarySearchIter(it A, it B, const T& V) {

	if (*A == V) { return A; }
	std::int64_t c = std::distance(A, B) / 2;
	if (*(A + c) == V) { return A + c; }
	if (c == 0) { return (*A) == V ? A : B; }


	it a = A;
	it b = B;

	do {
		c = std::distance(a, b) / 2;
		if (*(a + c) < V) {
			a += c;
			if (*a == V) { return a; }
		}
		else {
			b -= c;
			if (*b == V) { return  b; }
		}
	} while (c > 0);

	return  (*a) == V ? a : B;;
}

template<class T,class Container>
std::size_t BlockRetioSearch(const Container& D, const T& V,const std::size_t& Div) {
	if (D.size() == 0) { return D.size(); }
	std::size_t P = BlockSearchBlock(D, V, Div);
	double S = (D.size()-1) / (double)Div;
	auto it = BinarySearchIter(D.begin() + ((P - 1)*S), D.begin() + (P*S), V);

	return (*it) == V ? std::distance(D.begin(), it) : D.size();
}
template<class T,class Container>
std::size_t BinaryRatioSearch(const Container& D, const T& V, const std::size_t& Div) {
	std::size_t  P = BinarySearchBlock(D, V, Div);
	double S = D.size() / (double)Div;
	auto it = BinarySearchIter(D.begin() + (P*S), D.begin() + ((P+1)*S), V);
	return (*it) == V ? std::distance(D.begin(), it) : D.size();
}
/**/
int main() {
	DType D = MakeVector(((1 << 8) << 8));
	std::size_t Div = 7;

	for (std::size_t j = 2; j < Div; j++) {
		for (std::size_t i = 0; i < D.size(); i++) {
			if (BinaryRatioSearch(D, i, j) != D[i]) {
				std::cout << i<<":" <<j<< std::endl;

			}
		}
	}


	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/** /
int main() {
	DType D = MakeVector(((1 << 8) << 8));
	std::size_t Div = 7;

	for (std::size_t i = 0; i < D.size(); i++) {
		std::size_t P = BinarySearchBlock(D, i, Div);
		std::cout << i << ":" << P << std::endl;
	}

	
	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/* * /
int main() {
	DType D = MakeVector(((1<<8)<<8));
	std::size_t Div = 7;

	for (std::size_t j = 2; j < Div; j++) {
		for (std::size_t i = 0; i < D.size(); i++) {
			if (BlockRetioSearch(D, i, j) != D[i]) {
				std::cout << i <<":"<<j<< std::endl;

			}
		}
	}
	
	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/** /
int main() {
	DType D = MakeVector(((1<<8)<<8));
	std::size_t Div = 7;
	for (std::size_t i = 0; i < D.size(); i++) {
		if (BlockSearch(D, i,Div) != D[i]) {
			std::cout << i << std::endl;

		}
	}
	
	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/** /
int main() {
	DType D = MakeVector(((1<<8)<<8<<8));

	for (std::size_t i = 0; i < D.size(); i++) {
		if (BinarySearch(D, i) != D[i]) {
			std::cout << i << std::endl;

		}
	}
	
	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/** /
int main() {
	DType D = MakeVector(((1<<8)<<8<<8));

	for (std::size_t i = 0; i < D.size(); i++) {
		if ((*BinarySearchIter(D.begin(),D.end(), i)) != D[i]) {
			std::cout << i << std::endl;

		}
	}
	
	std::cout << "Complete!"<< std::endl;
	
	return 0;
}
/**/