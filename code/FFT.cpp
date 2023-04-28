typedef complex<double> cp;

const double pi = acos(-1);
const int NN = 131072;

struct FastFourierTransform{
	/*
		Iterative Fast Fourier Transform
		How this works? Look at this
		0th recursion 0(000)   1(001)   2(010)   3(011)   4(100)   5(101)   6(110)   7(111)
		1th recursion 0(000)   2(010)   4(100)   6(110) | 1(011)   3(011)   5(101)   7(111)
		2th recursion 0(000)   4(100) | 2(010)   6(110) | 1(011)   5(101) | 3(011)   7(111)
		3th recursion 0(000) | 4(100) | 2(010) | 6(110) | 1(011) | 5(101) | 3(011) | 7(111)
		All the bits are reversed => We can save the reverse of the numbers in an array!
	*/
	int n, rev[NN];
	cp omega[NN], iomega[NN];
	void init(int n_){
		n = n_;
		for(int i = 0;i < n_;i++){
			//Calculate the nth roots of unity
			omega[i] = cp(cos(2*pi*i/n_),sin(2*pi*i/n_));
			iomega[i] = conj(omega[i]);
		}
		int k = __lg(n_);
		for(int i = 0;i < n_;i++){
			int t = 0;
			for(int j = 0;j < k;j++){
				if(i & (1<<j)) t |= (1<<(k-j-1));
			}
			rev[i] = t;
		}
	}

	void transform(vector<cp> &a, cp* xomega){
		for(int i = 0;i < n;i++)
			if(i < rev[i]) swap(a[i],a[rev[i]]);
		for(int len = 2; len <= n; len <<= 1){
			int mid = len >> 1;
			int r = n/len;
			for(int j = 0;j < n;j += len)
				for(int i = 0;i < mid;i++){
					cp tmp = xomega[r*i] * a[j+mid+i];
					a[j+mid+i] = a[j+i] - tmp;
					a[j+i] = a[j+i] + tmp;
				}
		}
	}

	void fft(vector<cp> &a){ transform(a,omega); }
	void ifft(vector<cp> &a){ transform(a,iomega); for(int i = 0;i < n;i++) a[i] /= n;}
} FFT;