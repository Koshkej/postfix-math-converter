#include <iostream>
#include <vector>

std::string to_postfix(std::string infix);
std::vector<int> precedence(std::string infix);
void removebrackets(std::string &infix);
void replace(std::string &infix, std::vector<int> &preclist);
bool maxsimazie(std::vector<int> preclist, int checkposition);
int sumnumberlist(std::vector<int> preclist);

int main() {

	std::string postfix = to_postfix("2^2*(2-(2+2/3");

	for (int i = 0; i < postfix.size(); i++) {
		std::cout << postfix[i];
	}

	return 0;

}

std::string to_postfix(std::string infix) {

	std::vector<int> precedencelist = precedence(infix);
	removebrackets(infix);

	while (sumnumberlist(precedencelist) != 0) {
		replace(infix, precedencelist);
	}
	
	return infix;

}

void replace(std::string &infix, std::vector<int> &preclist) {
	int numoperation = -1;
	for (int i = 0; i < infix.size(); i++) {
		 if (infix[i] == '^' || infix[i] == '/' || infix[i] == '*' || infix[i] == '+' || infix[i] == '-') {
			numoperation++;
			if (maxsimazie(preclist, numoperation)) {
				preclist[numoperation] = 0;
				std::string buff = "";
				for (int y = i + 1; y < infix.size(); y++) {
					if (infix[y] == '0' || infix[y] == '1' || infix[y] == '2' || infix[y] == '3' || infix[y] == '4' ||
						infix[y] == '5' || infix[y] == '6' || infix[y] == '7' || infix[y] == '8' || infix[y] == '9')
					{
						buff.push_back(infix[y]);
					}
					else {
						int sizeinfo = buff.size();
						if (sizeinfo > 1) {
							for (int c = 0, no = 1; c + y < infix.size(); c++) {
								buff.push_back(infix[y + c]);
								if (infix[c + y + 1] == '^' || infix[c + y + 1] == '/' || infix[c + y + 1] == '*' || infix[c + y + 1] == '+' || infix[c + y + 1] == '-') {
									no++;
									if (preclist[numoperation + no] != 0) {
										break;
									}
								}
							}
						}
						break;
					}
				}
				infix[i + buff.size()] = infix[i];
				for (int r = i, m = 0; r < (i + buff.size()) && m < buff.size(); r++, m++) {
					infix[r] = buff[m];
				}
				break;
			}
		}
	}
}

std::vector<int> precedence(std::string infix) {
	std::vector<int> result;
	int parentheses = 0;
	for (int i = 0; i < infix.size(); i++) {
		switch (infix[i])
		{
		case '(':
			parentheses++;
			break;
		case ')':
			parentheses--;
			break;
		case '^':
			result.push_back(3 + 3 * parentheses);
			break;
		case '/': case '*':
			result.push_back(2 + 3 * parentheses);
			break;
		case '+': case '-':
			result.push_back(1 + 3 * parentheses);
			break;
		}
	}
	return result;
}

bool maxsimazie(std::vector<int> preclist, int checkposition) {
	int currentmax = 0;
	for (int i = 1; i < preclist.size(); i++) {
		if (preclist[i] > preclist[currentmax]) currentmax = i;
	}
	if (currentmax == checkposition) return true;
	else return false;
}

int sumnumberlist(std::vector<int> preclist) {
	int result = 0;
	for (int i = 0; i < preclist.size(); i++) {
		result += preclist[i];
	}
	return result;
}

void removebrackets(std::string &infix) {
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == ')' || infix[i] == '(') {
			infix.erase(i, 1);
		}
	}
}