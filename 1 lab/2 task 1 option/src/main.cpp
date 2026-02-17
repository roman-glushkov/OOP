/*
14.7. Скупой рыцарь (6)
Скупой рыцарь решил отмолить в монастыре грехи, не слишком рискуя состоянием. 
Он показал настоятелю монастыря в своем подвале N сундуков с монетами,  пронумерованных от 1 до N, и весы, 
позволяющие определить точный вес любого множества монет от одной до содержимого всех сундуков. 
В каждом сундуке находятся монеты одного из K типов. Монеты внешне неотличимы, но имеют разный вес: 1, 2, …,  K граммов. 
Рыцарь не сказал, какой тип монет находится в каждом сундуке. Более того, монеты некоторых типов могут вообще отсутствовать. 
Монастырь получит сундуки, если после единственного взвешивания некоторого набора монет будет выявлено, какой тип монет находится в каждом сундуке.
Настоятель монастыря определил для взвешивания следующий набор монет: из первого сундука выбрана одна монета,  
из второго K, из третьего K2, из четвертого K3 и т. д., то есть из N-го сундука KN-1 монет. 
Требуется по общему весу монет определить номера сундуков с каждым типом монет.
Ввод из файла INPUT.TXT. В первой строке содержатся  N  и  K (2 ≤ N ≤ 10; 2 ≤ K ≤ 8; K ≤ N). 
Во второй строке задан общий вес выбранного набора монет. Гарантируется, что для заданного веса имеется корректный ответ.
Вывод в файл OUTPUT.TXT. В первой строке указывается количество сундуков первого типа с монетами весом 1 грамм, 
а далее номера сундуков с монетами этого типа в порядке возрастания. Все числа разделяются пробелами. 
Если сундуков с такими монетами нет, то в строке содержится только значение 0. 
Во второй строке в аналогичном виде выводится информация о сундуках с монетами второго типа весом 2 грамма и т. д. 
Таким образом, вывод содержит K строк.
Глушкво Роман ПС - 22
C++ VSCode
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int CalculateMinimalRemainingWeight(int N, int K) {
    int minimalWeight = 0;
    for (int i = 0; i < N; i++) {
        minimalWeight += (int)pow(K, i);
    }
    return minimalWeight;
}

vector<int> DetermineChestTypes(int N, int K, int W) {
    vector<int> chestType(N + 1);

    int remainingWeight = W; //оставшийся вес
    int minimalTotalWeight = CalculateMinimalRemainingWeight(N, K); //минимальный общий вес
    int reservedWeight = 0; //зарезервированный вес

    for (int chestNumber = N; chestNumber >= 1; chestNumber--) {
        int chestMultiplier = (int)pow(K, chestNumber - 1); //число монет, взятых из сундука
        reservedWeight += chestMultiplier;
        int minimalForRest = minimalTotalWeight - reservedWeight; //минимальный остаток для последующих сундуков

        for (int coinType = K; coinType >= 1; coinType--) {
            int candidateWeight = chestMultiplier * coinType; //вес сундука

            if (candidateWeight <= remainingWeight && remainingWeight - candidateWeight >= minimalForRest) {
                chestType[chestNumber] = coinType; //сохранение результатов
                remainingWeight -= candidateWeight;
                break;
            }
        }
    }

    return chestType;
}

void OutputResult(ofstream& outputFile, const vector<int>& chestType, int N, int K) {
    for (int coinType = 1; coinType <= K; coinType++) {
        vector<int> chestsWithThisType; //Хранит номера сундуков

        for (int i = 1; i <= N; i++) {
            if (chestType[i] == coinType) {
                chestsWithThisType.push_back(i);
            }
        }

        if (chestsWithThisType.empty()) {
            outputFile << 0;
        } else {
            outputFile << chestsWithThisType.size();
            for (int chest : chestsWithThisType) {
                outputFile << " " << chest;
            }
        }
        outputFile << endl;
    }
}

int main() {
    ifstream inputFile("INPUT.TXT");
    ofstream outputFile("OUTPUT.TXT");

    int N, K;
    inputFile >> N >> K;

    int W;
    inputFile >> W;

    vector<int> chestType = DetermineChestTypes(N, K, W);
    OutputResult(outputFile, chestType, N, K);

    return 0;
}
