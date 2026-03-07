#include "long_number.hpp"

using ypa::LongNumber;
		
LongNumber::LongNumber() {
	len = 1;
	sign = 0;
	digits = new int[len]{0};
}

LongNumber::LongNumber(int length, int sign): len(length), sign(sign) {
	this->len = length;
	this->sign = sign;
	this->digits = new int[len]{0};
}

LongNumber::LongNumber(const char* const str) {
	const char* ptr = str;

	if (*ptr == '-') {
		sign = 1;
		++ptr;
	} else {
		sign = 0;
	}

	while (*ptr == '0') ++ptr;

	const char* end = ptr;
	while (*end >= '0' && *end <= '9') ++end;
	len = end - ptr;

	digits = new int[len];
	for (int i = 0; i < len; ++i) {
		digits[i] = end[-1 - i] - '0';
	}


}

LongNumber::LongNumber(const LongNumber& x) {
	//копирование числа по знакам в другую переменную
	len = x.len;
	sign = x.sign;
	digits = new int[len];
	for (int i = 0; i < len; ++i) {
		digits[i] = x.digits[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	//перемещение не по знакам а в целом
	digits = x.digits;
	len = x.len;
	sign = x.sign;

	x.digits = nullptr;
	x.len = 0;
	x.sign = 0;
}

LongNumber::~LongNumber() {
	//деструктор
	delete[] digits;
	len = 0;
	digits = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	LongNumber temp(str);

	delete[] digits;

	digits = temp.digits;
	len = temp.len;
	sign = temp.sign;

	temp.digits = nullptr;

	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
		delete[] digits;

		len = x.len;
		sign = x.sign;
		digits = new int[len];

		for (int i = 0; i < len; ++i) {
			digits[i] = x.digits[i];
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this != &x) {
		delete[] digits;

		digits = x.digits;
		len = x.len;
		sign = x.sign;

		x.digits = nullptr;
		x.len = 0;
		x.sign = 0;
	}
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] ==  0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);

	if (this_zero && x_zero) return true;
	if (this_zero || x_zero) return false;
	if (sign != x.sign) return false;
	if (len != x.len) return false;

	for (int i = 0; i < len; ++i) {
		if (digits[i] != x.digits[i]) return false;
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	if (*this == x) return false;
	return true;
}

bool LongNumber::operator > (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] ==  0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);

	if (this_zero && x_zero) return false;
	if (this_zero) return x.sign == 1;
	if (x_zero) return sign == 0;
	if (x == *this) return false;

	if (sign != x.sign) return sign < x.sign;

	if (sign == 1) {
		if (len != x.len) return len < x.len;
		for (int i = len - 1; i >= 0; --i) {
			if (digits[i] != x.digits[i]) return digits[i] < x.digits[i];
		}
		return false;
	}

	if (len != x.len) return len > x.len;
	for (int i = len - 1; i >= 0; --i) {
		if (digits[i] != x.digits[i]) return digits[i] > x.digits[i];
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return (x > *this);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] == 0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);

	if (this_zero) return x;
	if (x_zero) return *this;

	if (sign != x.sign) {
		if (sign == 1) {
			LongNumber temp = *this;
			temp.sign = 0;
			return x - temp;
		} else {
			LongNumber temp = x;
			temp.sign = 0;
			return *this - temp;
		}
	}
	LongNumber result;
	delete[] result.digits;

	int maxLen = (len > x.len ? len : x.len) + 1;
	result.len = maxLen;
	result.digits = new int[maxLen]{0};
	result.sign = sign;

	int carry = 0;
	for (int i = 0; i < maxLen; ++i) {
		int sum = carry;
		if (i < len) sum += digits[i];
		if (i < x.len) sum += x.digits[i];

		result.digits[i] = sum % 10;
		carry = sum / 10; 
	}

	while (result.len > 1 && result.digits[result.len - 1] == 0) {
    	result.len--;
	}
	return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] == 0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);

	if (this_zero and x_zero) return LongNumber(1, 0);;
	if (this_zero) {
		LongNumber result = x;
		result.sign = !x.sign;
		return result;
	}
	if (x_zero) return *this;

	if (sign != x.sign) {
		LongNumber temp = x;
		temp.sign = !temp.sign;
		return *this + temp;
	}

	if (sign == 1) {
		LongNumber a = *this;
		LongNumber b = x;
		a.sign = 0;
		b.sign = 0;
		return b - a;
	}

	bool a_less_b = false;
	if (len != x.len) {
		a_less_b = len < x.len;
	} else {
		for (int i = len - 1; i >= 0; --i) {
			if (digits[i] != x.digits[i]) {
				a_less_b = digits[i] < x.digits[i];
				break;
			}
		}
	}
	if (a_less_b) {
		LongNumber result = x - *this;
		result.sign = 1;
		return result;
	}
	LongNumber result;
	delete[] result.digits;

	result.len = len;
	result.digits = new int[len];
	result.sign = 0;

	int borrow = 0; //перенос из следую	ё	щего разряда
	for (int i = 0; i < len; ++i) {
		int sub = digits[i] - borrow; //текущая цифра в разряде
		if (i < x.len) sub -= x.digits[i];

		if (sub < 0) {
			sub += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		result.digits[i] = sub;
	}

	while (result.len > 1 && result.digits[result.len - 1] == 0) {
		--result.len;
	}

	return result;
}


LongNumber LongNumber::operator * (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] == 0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);
    if (this_zero || x_zero) return LongNumber(1, 0);
    
    LongNumber result(len + x.len + 1, sign ^ x.sign);
    
    for (int i = 0; i < x.len; i++) {
        for (int j = 0; j < len; j++) {
            result.digits[i + j] += x.digits[i] * digits[j];
            
            if (result.digits[i + j] > 9) {
                int carry = result.digits[i + j] / 10;
                result.digits[i + j + 1] += carry;
                result.digits[i + j] %= 10;
            }
        }
    }
    
    while (result.len > 1 && result.digits[result.len - 1] == 0) {
        result.len--;
    }
    
    return result;
}


LongNumber LongNumber::operator / (const LongNumber& x) const {
	bool this_zero = (len == 1 && digits[0] == 0);
	bool x_zero = (x.len == 1 && x.digits[0] == 0);
	if (this_zero) return LongNumber(1, 0);

    LongNumber dividend = *this; 
    dividend.sign = 0;
    LongNumber divisor_positive = x;
    divisor_positive.sign = 0;
    
    if (dividend < divisor_positive) {
        return LongNumber(1, 0);
    }

    LongNumber result;
    result = LongNumber(len - x.len + 1, sign ^ x.sign);
    for (int i = 0; i < result.len; i++) {
        LongNumber shifted_divisor = LongNumber(len - i, 0);
        
        for (int j = 0; j < x.len; j++) {
            shifted_divisor.digits[len - x.len - i + j] = divisor_positive.digits[j];
        }
        
        int counter = 0;
        while (dividend > shifted_divisor || dividend == shifted_divisor) {
            counter++;
            dividend = dividend - shifted_divisor;
        }
        result.digits[result.len - i - 1] = counter;
    }
    
    while (result.len > 1 && result.digits[result.len - 1] == 0) {
        result.len--;
    }
    
    return result;
}


LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber divisor_positive = x;
    divisor_positive.sign = 0;

    LongNumber dividend = *this;
    dividend.sign = 0;
    
    LongNumber result;
    result = dividend - (dividend / divisor_positive) * divisor_positive;
    
    if (sign == 1) {
        result.sign = 1;
    }
    
    return result;
}

bool LongNumber::is_negative() const noexcept {
	if (len == 1 && digits[0] == 0) return false;
	return sign == 1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	if (!str) return 0;

	int i = 0;
	if (str[i] == '-' || str[i] == '+') {
		++i;
	}
	if (str[i] < '0' || str[i] > '9') return 0;

	int length = 0;
	while (str[i] >= 0 && str[i] <= '9') {
		++length;
		++i;
	}
	if (str[i] != '\0') return 0;

	return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace ypa {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.len == 1 && x.digits[0] == 0) {
			os << '0';
			return os;
		}

		if (x.sign) {
			os << '-';
		}
		for (int i = x.len - 1; i >= 0; --i) {
			os << x.digits[i];
		}
		return os;
	}
}