#pragma once
struct TMonom
{
	int coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom() : coef(0), index(0) {}

	TMonom::TMonom(int cval, int degX, int degY, int degZ) : coef(cval) {
		if (degX < 0 || degX > 9 || degY < 0 || degY > 9 || degZ < 0 || degZ > 9) {
			throw std::invalid_argument("Invalid exponent value.");
		}
		index = (degX * 100) + (degY * 10) + degZ;
	}

	void SetCoef(int cval) { 
		coef = cval;
	}
	int GetCoef(void) { 
		return coef; 
	}

	void SetIndex(int ival) {
		index = ival; 
	}
	int GetIndex(void) { 
		return index; 
	}


	bool operator==(const TMonom& other) {
		return coef == other.coef && index == other.index;
	}
	
	bool operator>(const TMonom& other) { 
		return index > other.index;
	}

	bool operator<(const TMonom& other) {
		return index < other.index;
	}


};