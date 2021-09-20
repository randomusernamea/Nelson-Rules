#include <algorithm>

//Returns the position of the first point that is more than 3 std away from the mean.
int rule1(int a[], int mean, int std) {
	int aux = 0;
	while (aux < sizeof(a)) {
		if ((a[aux] > mean + 3 * std) || (a[aux] < mean - 3 * std )) {
			return aux;
		}
		aux++;
	}
	return -1;
}

//Returns the position of the first point that is the 9th point to be on the same side of the mean.
int rule2(int a[], int mean, int std) {
	int aux = 0;
	int count = 0;
	while (aux < sizeof(a)) {
		if (a[aux] > mean) {
			count = std::max(count + 1, 0);
			if (count > 8) {
				return aux;
			}
		}
		else if (a[aux] < mean) {
			count = std::min(count - 1, 0);
			if (count < -8) {
				return aux;
			}
		}
		else {
			count = 0;
		}
	aux++;
	}
	return -1;
}

//Returns the position of the first point to be the sixth point to continually increase or decrease.
int rule3(int a[], int mean, int std) {
	if (sizeof(a) < 6) {
		return -1;
	}
	int aux = 1;
	int count = 0;
	while (aux < sizeof(a)) {
		if (a[aux] > a[aux - 1]) {
			count = std::max(count + 1, 0);
			if (count > 5) {
				return aux;
			}
		}
		else if (a[aux] < a[aux - 1]) {
			count = std::min(count - 1, 0);
			if (count < -5) {
				return aux;
			}
		}
		else {
			count = 0;
		}
	}
	return -1;
}

//Returns the position of the first point to be the 14th point to alternate between an increase and decrease in value.
int rule4(int a[], int mean, int std) {
	if (sizeof(a) < 14) {
		return -1;
	}
	int aux = 2;
	int count = 2;
	bool hasToDecrease = false;
	if (a[0] < a[1]) {
		hasToDecrease = true;
	}
	while (aux < sizeof(a)) {
		if (a[aux] > a[aux - 1]) {
			if (hasToDecrease = false) {
				count++;
				if (count > 13) {
					return aux;
				}
				hasToDecrease = true;
				aux++;
				continue;
			}
			else {
				count = 2;
				hasToDecrease = true;
				aux++;
				continue;
			}
		}
		else if (a[aux] == a[aux - 1]) {
			count = 2;
			aux++;
			if (aux < sizeof(a)) {
				if (a[aux] > a[aux - 1]) {
					hasToDecrease = true;
				}
				else {
					hasToDecrease = false;
				}
			}
			else {
				return 0;
			}
			aux++;
			continue;
		}
		else {
			if (hasToDecrease = true) {
				count++;
				if (count > 13) {
					return aux;
				}
				hasToDecrease = false;
				aux++;
				continue;
			}
			else {
				count = 2;
				hasToDecrease = false;
				aux++;
				continue;
			}
		}

		aux++;
	}
	return -1;
}

//Returns the first point of a triplet that cointains two or three points more than two standard deviations away in the same direction
int rule5(int a[], int mean, int std) {
	if (sizeof(a) < 2) {
		return -1;
	}
	int aux = 2;
	int countTwo = 0;
	int countOne = 0;
	int countActual = 0;
	if (a[0] > mean + 2 * std) {
		countOne = 1;
	}
	else if (a[0] < mean - 2 * std) {
		countOne = -1;
	}

	if (a[0] > mean + 2 * std) {
		countActual = 1;
	}
	else if (a[0] < mean - 2 * std) {
		countActual = -1;
	}
	if (countOne + countActual > 1) {
		return 0;
	}
	else if (countOne + countActual < -1) {
		return 0;
	}
		
	while (aux < sizeof(a)) {
		countTwo = countOne;
		countOne = countActual;
			if (a[aux] < mean - 2 * std) {
				countActual = -1;
					if ((countTwo + countActual < -1) || countOne + countActual < -1) {
						return aux - 2;
					}
			}
			else if (a[aux] > mean + 2 * std) {
				countActual = 1;
				if ((countTwo + countActual > 1) || countOne + countActual > 1) {
					return aux - 2;
				}
		}
		else {
			countActual = 0;
		}
		
		aux++;
	}
	return -1;
}


//Returns the first point of a set of five points in a row that contains at least four points outside of one std from the mean in the same direction.
int rule6(int a[], int mean, int std) {
	if (sizeof(a) < 2) {
		return -1;
	}
	int aux = 2;
	int countFour = 0;
	int countThree = 0;
	int countTwo = 0;
	int countOne = 0;
	int countActual = 0;

	if (a[3] > mean + std) {
		countActual = 1;
	}
	else if (a[3] < mean - std) {
		countActual = -1;
	}

	if (a[2] > mean + std) {
		countOne = 1;
	}
	else if (a[2] < mean - std) {
		countOne = -1;
	}

	if (a[1] > mean + std) {
		countTwo = 1;
	}
	else if (a[1] < mean - std) {
		countTwo = -1;
	}

	if (a[0] > mean + std) {
		countThree = 1;
	}
	else if (a[0] < mean - std) {
		countThree = -1;
	}



	else if (std::max(countThree, 0) + std::max(countTwo, 0) + std::max(countOne, 0) + std::max(countActual, 0) < -3) {
		return 0;
	}

	else if (std::min(countThree, 0) + std::min(countTwo, 0) + std::min(countOne, 0) + std::min(countActual, 0) > 3) {
		return 0;
	}

	while (aux < sizeof(a)) {
		countFour = countThree;
		countThree = countTwo;
		countTwo = countOne;
		countOne = countActual;
		if (a[aux] < mean - 1 * std) {
			countActual = -1;
				if (std::max(countFour,0) + std::max(countThree, 0) + std::max(countTwo, 0) + std::max(countOne, 0) + std::max(countActual, 0) < -3) {
					return aux - 4;
				}
		}
		else if (a[aux] > mean + 1 * std) {
			countActual = 1;
			if (std::min(countFour,0) + std::min(countThree, 0) + std::min(countTwo, 0) + std::min(countOne, 0) + std::min(countActual, 0) > 3) {
				return aux - 4;
			}
		}
		else {
			countActual = 0;
		}

		aux++;
	}
	return -1;
}

int rule7(int a[], int mean, int std) {
	if (sizeof(a) < 15) {
		return -1;
	}
	int aux = 0;
	int count = 0;
	while (aux < 14) {
		if ((a[aux] < mean + std) && (a[aux] > mean + std)) {
			count++;
		}
		aux++;
	}
	if (count > 14) {
		return 0;
	}
	while (aux < sizeof(a)) {
		if ((a[aux] < mean + std) && (a[aux] > mean + std)) {
			count++;
		}
		if ((a[aux-15] < mean + std) && (a[aux-15] > mean + std)) {
			count--;
		}
		if (count > 14) {
			return aux-14;
		}
		aux++;
	}
	return -1;
}


//Returns the first point to be the 8th consecutive one to be outside of one std of the mean and there are points in both sides of the mean.
int rule8(int a[], int mean, int std) {
	if (sizeof(a) < 8) {
		return -1;
	}
	bool overMean = false;
	bool underMean = false;
	int lastWithinAMean = -1;
	int aux = 0;
	while (aux < sizeof(a)) {
		if (a[aux] > mean + std) {
			overMean = true;
		}
		else if (a[aux] < mean - std) {
			underMean = true;
		}
		else {
			lastWithinAMean = aux;
		}
		if (underMean && overMean && lastWithinAMean < aux - 7) {
			return aux;
		}
		aux++;
	}
}