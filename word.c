#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define MAX_MEANING_LENGTH 100
#define MAX_DICTIONARY_SIZE 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
} WordEntry;

void shuffleArray(int* array, int size) {//�迭�� ���� �������� ���� �Ǽ�-������ ���� �˰��� ���
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    
    srand(time(NULL));

    
    WordEntry dictionary[MAX_DICTIONARY_SIZE];

    
    const char* filePath = "C:\\Users\\a9125\\OneDrive\\���� ȭ��\\words.txt";//������� �޸��� ���� ��ġ�� ����(����ڸ��� �ٸ��⿡ ���� �ʿ�)

    
    FILE* file = fopen(filePath, "r");//���� �ҷ����� ���� �߻� �� ���
    if (file == NULL) {
        printf("���� ������ �� �� �����ϴ�.\n");
        return 1;
    }

    // �ܾ� ���� �� ���� ������ �ʱ�ȭ
    int wordCount = 0;
    char line[MAX_WORD_LENGTH + MAX_MEANING_LENGTH + 2];
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = '\0';

        // �ܾ�� �� ó�� tab�� ���� ó����
        char* word = strtok(line, "\t");
        char* meaning = strtok(NULL, "\t");

        if (word != NULL && meaning != NULL) {
            strncpy(dictionary[wordCount].word, word, sizeof(dictionary[wordCount].word));
            strncpy(dictionary[wordCount].meaning, meaning, sizeof(dictionary[wordCount].meaning));
            wordCount++;
        }
    }

    fclose(file);

    // �������� 30���� �ܾ� ����(�÷����� 30������ ���� �����̱⿡ 30���� ������. �� �κ��� �̿����� ��ȣ�� ���� ������ �ٲ� �� ����;�ٸ� 30�� ���õ� ��� ���� �����ؾ� �ȴ�)
    if (wordCount > 0) {//�ܾ� �����Ͱ�>0 �� ������ �� ����
        int randomIndices[MAX_DICTIONARY_SIZE];//������ �ε��� �迭 ����
        for (int i = 0; i < wordCount; i++) {
            randomIndices[i] = i;
        }

        shuffleArray(randomIndices, wordCount);//�ʹݺο� ������ �˰����� �̿��� �迭 �������� ����

        printf("=== ���ܾ� �ϱ� ���α׷� ===\n");
        printf("30���� ���ܾ� ���� ���纸����.\n");

        int score = 0;
        for (int i = 0; i < 30 && i < wordCount; i++) {//������ ���������� 30��
            int index = randomIndices[i];
            WordEntry* entry = &dictionary[index];

            printf("\n�ܾ� #%d: %s\n", i + 1, entry->word);//�ܾ� ����

            char userMeaning[MAX_MEANING_LENGTH];//�Է��� �ܾ� ���
            printf("���� �Է��ϼ���: ");
            fgets(userMeaning, sizeof(userMeaning), stdin);

            
            userMeaning[strcspn(userMeaning, "\n")] = '\0';

            if (strcmp(userMeaning, entry->meaning) == 0) {
                printf("�����Դϴ�!\n");
                score++;
            }
            else {
                printf("Ʋ�Ƚ��ϴ�. ������ '%s'�Դϴ�.\n", entry->meaning);
            }
        }

        printf("\n�ϱ� ����: %d / 30\n", score);//���� ������ �����ش�
    }
    else {//�޸��忡 ����� �ܾ ���� �� �⤩���Ѵ�
        printf("������ �ܾ �����ϴ�.\n");
    }

    return 0;
}
//���ǻ���:�ѱ� Ư���� �� ��� �ƴϱ⿡ ������ ������ �߻��� ���� �ִµ�, �ܾ����� �޸����� ansi���·� ���ڵ��Ͽ� �����Ѵٸ� �ذ��� �ȴ�.
//���� �ܾ����� ���� �� ���α׷��� �ۼ��ȴ�� ��� ���� �ܾ tab���� �����Ͽ� �ۼ��ؾߵȴ� (������{����ܾ�tab��})
/*
����
apple	���
banana	�ٳ���
carrot	���
dog	��
elephant	�ڳ���
fox	����
grape	����
hat	����
ice cream	���̽�ũ��
jacket	��Ŷ
kangaroo	Ļ�ŷ�
lion	����
mango	����
nut	�߰���
orange	������
pencil	����
queen	����
rabbit	�䳢
strawberry	����
tiger	ȣ����
umbrella	���
vase	�ɺ�
watermelon	����
xylophone	�Ƿ���
yacht	��Ʈ
zebra	��踻
ear	��
mouth	��
time	�ð�
wind	�ٶ�

�̷������� �ۼ��ϸ� �ȴ�




*/