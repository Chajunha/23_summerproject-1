#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_MEANING_LENGTH 100
#define MAX_DICTIONARY_SIZE 100
#define NUM_WORDS 20
#define DISPLAY_TIME 1000 // �ܾ� �� �� �����ִµ� ��� �ð� 1�� (�и��� ������ ǥ��)
#define INPUT_TIME 5000  // �ܾ� �� �� �Է��ϴµ� �־��� �ð� 5�� (�и��� ����)
#define N 41

int see();
int memorize();


struct Word {
    char korean[50];
    char english[50];
    char hint[50];
};

typedef struct {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
} WordEntry;

void print_start()
{
    printf("Select the game!!!\n");
    printf("1. animal_quiz\n");
    printf("2. city_quiz\n");
    printf("3. fruit_quiz\n");
}
void shuffleArray(int* array, int size);
void showing_word(char* word); // �ܾ �����ش�
void fade_away(); // ȭ�� ������� ��
int arrange(const void* a, const void* b); // qsort �Լ��� ����� �� �Լ�


int main()
{
    int pjh0917 = 0;

    int point = 0;
    char* animal_quiz[NUM_WORDS] = {
        "human","tiger","dragon","monkey","bird",
        "cormorant","armadillo","pigeon","parrot","dog",
        "cat","killer whale","anteater","sloth","fox",
        "jaguar","puma","capybara","lion","boar"
    }; // ������ �ܾ��

    char* city_quiz[NUM_WORDS] = {
        "Seoul","Busan","Suwon","Rome","Madrid",
        "Beijng","New York","London","Cairo","Berlin",
        "Athene","Istanbul","Barcelona","Manchester","Moscow",
        "Pyongyang","Dubai","Toronto","Manhatton","Shanghai"
    };// ������ ���� �ܾ��

    char* fruit_quiz[NUM_WORDS] = {
        "apple","pear","watermelon","melon","banana",
        "mango","lemon","peach","plum","grape",
        "cherry","kiwi","coconut","pineapple","strawberry",
        "rasberry","blackberry","papaya","durian"
    };//������ ���� �ܾ��
    int a = 0;


    printf("����ϰ� ���� ���α׷� ��ȣ �Է� :\n1. �޸��� �ܾ��� ���α׷�\n2. Ÿ�Ӿ��� �ܾ� ����\n3.?\n4.?\n");
    
    scanf("%d", &pjh0917);
    getchar();

    switch (pjh0917)
    {
    case 1:

        //////////////////

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
        break;


    case 2:

        print_start();
        int selection;
        scanf_s("%d", &selection);
        char** quiz_selected = NULL;
        int num_words = 0;

        switch (selection)
        {
        case 1:
            quiz_selected = animal_quiz;
            num_words = sizeof(animal_quiz) / sizeof(animal_quiz[0]);
            break;
        case 2:
            quiz_selected = city_quiz;
            num_words = sizeof(city_quiz) / sizeof(city_quiz[0]);
            break;
        case 3:
            quiz_selected = fruit_quiz;
            num_words = sizeof(fruit_quiz) / sizeof(fruit_quiz[0]);
            break;
        default:
            printf("It's not a proper number.\n");
            return 0;
        }

       

        printf("Press Enter to start the game!!");
        getchar(); // �Է��� �޴´�

        // �ܾ���� ���� ������ ����
        qsort(quiz_selected, NUM_WORDS, sizeof(char*), arrange);



        for (int i = 0; i < NUM_WORDS; i++)
        {
            printf("\nCurrent Score: %d\n", point);
            showing_word(quiz_selected[i]); // �Ű����� animal_quiz[i]�� �ܾ �Ű������� ����
            Sleep(DISPLAY_TIME); // Sleep �Լ��� ����Ͽ� display_time�� �ð� 1�ʸ�ŭ �Ͻ������� ��Ű�� ��
            fade_away();

            printf("\n%s", "Enter the word: ");
            time_t timestart = time(NULL); // time(NULL) �Լ��� �ý����� ���� �ð��� �� ������ ��ȯ, time_t�� �ð� ������ �����ϴ� ������ ����, ���ӿ��� �ð� ������ �����ϴµ� ����ϴ� �ڵ�. timestart�� ���� �ð��� ���������ν� �÷��̾ �ܾ �Է��ϱ� ������ �ð��� ���.

            while (difftime(time(NULL), timestart) * 1000 <= INPUT_TIME) // c���� difftime �Լ��� ������ ����� �� ���, difftime(time(NULL), timestart)�� ���� �ð��� timestart ������ ���̸� �� ������ ��ȯ.
            {
                if (_kbhit()) // Ű�� Ű���忡�� ���ȴ��� Ȯ���Ѵ�.
                {
                    char wordinput[200];

                    fgets(wordinput, sizeof(wordinput), stdin); // stdin���� ����ڰ� Ű����� �Է��� ���ڿ��� wordinput �迭�� �����Ѵ�. sizeof(wordinput)�� wordinput �迭�� ũ�⸦ ��Ÿ����. �Է¹��� �ִ� ���ڿ� ���̸� �����Ѵ�->�����÷ο� ����, stdin ����ؼ� Ű����� �Է��� ���ڿ��� ���α׷����� �޾ƿ´�. fgets �Լ� ��ü�� �Էµ� ���ڵ�� �Բ� ���๮�ڸ� �Է¹��ۿ��� �����´�.

                    wordinput[strcspn(wordinput, "\n")] = '\0'; // ���� ����ڰ� �Է��� ���ڿ��� wordinput�� ����Ǿ� �ִ�. strcspn�� wordinput ���ڿ����� ���๮�� "\n"�� ó������ ��Ÿ���� ��ġ�� ã�Ƽ� ��ȯ�Ѵ�. �׸��� �̰��� �η� �ٲ��ش�.

                    if (strcmp(wordinput, quiz_selected[i]) == 0) // strcmp�� ���ڿ��� ���ϴ� �Լ� string.h���� �����´�. strcmp�� ()�ȿ� ���Ϸ��� ���ڿ��� ������ 0�̶�� �Ѵ�.
                    {
                        point += 1;
                    }
                    else
                    {
                        point -= 1;
                    }
                    break;
                }
            }

            showing_word("Next word will appear!!!");
            Sleep(DISPLAY_TIME);
            fade_away();
        }

        printf("\n\nGame Over! Your Record is %d\n", point);

        return 0;
        break;


    case 3:


        printf("***���α׷� ��� �ܾ���***\n\n");
        printf("������� ���÷��� '1', �ϱ�븦 ���÷��� '2'�� �����ּ���.\n");
        scanf(" %d", &a);

        if (a == 1) {
            see();
        }
        else if (a == 2) {
            memorize();
        }
        else {
            while (1) {
                printf("'1'�Ǵ� '2' �� �߿� �ϳ��� ����ֽʽÿ�.\n");
                scanf(" %d", &a);
                if (a == 1) {
                    see();
                    break;
                }
                else if (a == 2) {
                    memorize();
                    break;
                }
            }
        }
        return 0;

        break;


    case 4:
        printf("\n# English word guessing program #\n");
        printf("(If you want a hint, type 'hint')\n\n");

        struct Word words[] = {
            { "����, ����; ����", "approval", "starting with 'a', 8 letters" },
            { "����; �����ϴ�; �����ϴ�", "bear", "starting with 'b', 4 letters" },
            { "�������; ����", "captive", "starting with 'c', 7 letters" },
            { "����", "disclosure", "starting with 'd', 10 letters" },
            { "������; ����ϴ� ��", "equivalent", "starting with 'e', 10 letters" },
            { "�����ϰ� �ϴ�", "facilitate", "starting with 'f', 10 letters" },
            { "����; ������ϴ�", "grudge", "starting with 'g', 6 letters" },
            { "�����ϴ�", "hinder", "starting with 'h', 6 letters" },
            { "�����ϴ�; �ΰ��ϴ�", "impose", "starting with 'i', 6 letters" },
            { "���ǲ�� ���̴�", "loom", "starting with 'l', 4 letters" },
            { "�պ��ϴ�", "merge", "starting with 'merge', 5 letters" },
            { "������", "permeate", "starting with 'p', 8 letters" },
            { "�����ϴ�; ������", "renounce", "starting with 'r', 8 letters" },
            { "����, ���", "solidarity", "starting with 's', 10 letters" },
            { "�ǽ��� ��������", "unquestionable", "starting with 'u', 14 letters" },
            { "�����ϴ�", "validate", "starting with 'v', 8 letters" },
            { "��������; öȸ�ϴ�; Ż���ϴ�", "withdraw", "starting with 'withdraw', 8 letters" },
            // �ܾ�, ��, ��Ʈ �ʿ��� ������ŭ �߰� ����
        };

        int totalWords = sizeof(words) / sizeof(words[0]);
        int randomIndex;
        char guess[50];
        int correctCount = 0;
        int incorrectCount = 0;

        srand(time(0));

        while (correctCount + incorrectCount < totalWords) {
            // ���� �������� ���� �ܾ� �� �������� ����
            do {
                randomIndex = rand() % totalWords;
            } while (words[randomIndex].english[0] == '\0'); // �̹� ������ �ܾ��� ��� �ٽ� ����

            printf("%s\n", words[randomIndex].korean);
            scanf("%s", guess);

            // ��Ʈ�� ���ϴ� ��� ��Ʈ ����, �̾ ���� Ǯ��
            if (strcmp(guess, "hint") == 0) {
                printf("%s\n\n", words[randomIndex].hint);
                printf("%s\n", words[randomIndex].korean);
                scanf("%s", guess);
            }

            // ������ ���Ͽ� ���� ���θ� �Ǵ��ϰ� ��� ����
            if (strcmp(guess, words[randomIndex].english) == 0) {
                printf("Correct!\n\n");
                correctCount++;
            }
            else {
                printf("Incorrect. The answer is %s.\n\n", words[randomIndex].english);
                incorrectCount++;
            }

            // �̹� ������ �ܾ�� ǥ���Ͽ� �ߺ� ���� ����
            words[randomIndex].english[0] = '\0';
        }

        // ��� ������ Ǭ �� �ǵ�� ����
        printf("*** RESULT ***\n");
        printf("Number of correct words: %d\n", correctCount);
        printf("Number of incorrect words: %d\n", incorrectCount);
        printf("Accuracy: %.2f%%\n\n", (float)correctCount / totalWords * 100);

        // �ٽ� �õ� ���θ� ���� �޽��� ���
        char tryAgain;
        printf("You've completed all the words. Do you wanna try again? (y/n): ");
        scanf(" %c", &tryAgain);

        if (tryAgain == 'y' || tryAgain == 'Y') {
            // ����ڰ� �ٽ� �õ��ϴ� ��� - ������ �ܾ �ʱ�ȭ�ϰ� ���� �����
            for (int i = 0; i < totalWords; i++) {
                words[i].english[0] = words[i].korean[0]; // �������� ���� ���� �ܾ �ٽ� �ʱ�ȭ
            }
            correctCount = 0;
            incorrectCount = 0;
            main(); // �Լ��� ��ȣ���Ͽ� ���� �����
        }
        else {
            // ����ڰ� ��õ����� �ʴ� ��� - ���α׷� ����
            printf("Thank you for playing!\n");
        }
        return 0;

    }
}


void showing_word(char* word)
{
    printf("\n****************************************\n");
    printf("            wordinput:%s                \n", word);
    printf("\n****************************************\n");
}

void fade_away()
{
    system("cls"); // window �ü������ ����ϴ� ��. ���� ȭ�鿡 ��µ� ������ ��� �����ִ� ��. cls -> clear screen
}

int arrange(const void* a, const void* b)
{
    // ���� ���� ���Ͽ� ����
    return strlen(*(char**)a) - strlen(*(char**)b);
}

void shuffleArray(int* array, int size) {//�迭�� ���� �������� ���� �Ǽ�-������ ���� �˰��� ���
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int see() {
    printf("���⼭���ʹ� '�����' �ܾ����Դϴ�.\n");

    char list1[N][20] = { "��ó��", "������","��ũ" "�Լ�","printf ","Stdio.h", " �����","���","����","int",
    "double","char","Scanf","���������","���Կ�����","����������","���迬����","��������","sizeof������","���ǿ�����",
    "if��","if~else��", "If~else if~else��","Switch~case��","while��", "�Լ� ����","�Լ� ����","�Լ� ȣ��","�迭", "gets",
    "for��","do~while��","gets", "puts",  "������","strcpy","strlen","strcat", "strcmp","��������",
    "��������","������������" };//42��

    char list2[N][100] = { "NULL","NULL","NULL","NULL",  "printf(��  ��);" , "Include <stdio.h> ","NULL", "Ex. �¾ �ð�(���), �������� �θ�� ",  "Ex. ����, Ű, ������",
    "int age; ","double height; ", "char food; ", "scanf(��%d��, &a); ", "c=a+b;,c=a-b;c=a/b;, c=a*b; c=a%b; ", "=  ",
    "++a;, b++;, --c;, d--; ", "a>b;, a<b;, a>=b;, a<=b;, a==b;, a!=b; ","(a>10)&&(a>7);,(a>10)||(a>7);,!(a>10); ",
     "sizeof(������ �Ǵ� �ڷ���) ","(����) ? (���� ��) : (������ ��);", "If(���ǽ�) ���๮; ", "if(���ǹ�) ���๮1; else ���๮2; ",
    " else if (���ǹ�2) ���๮2;else ���๮; ", "switch(���ǽ�){ case�����1; ���๮; break;case �����2; ���๮; break;default; ���๮; break; } ",
     "while(���ǽ�){ ���๮; } ", "������ �Լ���(������,1 ������2); ", "������ �Լ� �̸�(������1,������2){���; reture ��ȯ��;} ",
    "�Լ��̸�(������3,������4) ; ", "�ڷ��� �迭��[N]={��1,��2,��3.....��N}; ","for(�ʱ��; ���ǽ�; ������){ ���๮; } ",
    "Do{���๮; }while (���ǽ�); ",  "gets(�迭��); ","puts(�迭��); ", "������ *�����͸�=&������ ",
    "Strcpy(���ڿ�1,���ڿ�2); ","Strlen(���ڿ�); ", "Strcat(���ڿ�1, ���ڿ�2); ",  "strcmp (���ڿ�1, ���ڿ�2); ",
     "�Լ� �ȿ��� ���� ���� ", "�Լ��ۿ��� ���� ���� ","static ������ ������;  " };

    char list3[N][250] = {
     "��ó�� �����ڿ� ���� �ҽ������� �����ϴ� ����"
    ,"CPU�� �ؼ��� �� �ִ� ��ɾ��� ������ ��ü���Ϸ� �ٲٴ� ���� "
    ,"��ü���Ͽ� startup code�� �����ϴ� ���� "
    ,"�Ӹ�(�Լ� ����)�� �������� �����Ǿ� �ִ�. "
    ,"ȭ�鿡 �����͸� ������ ���Ŀ� ���� ����� �� �ִ�."
    ,"C���� �⺻���� ����ϴ� ����� �Լ��� �� �ִ�."
    ,"NULL"
    ,"���� ������ �ʴ� ������ "
    ,"���� �ٲ�� ������ "
    ,"������ �� �ϳ��� ������ ���� �� �ִ�. ���õ� ��� ��ȯ ����: %d "
    ,"������ �� �ϳ��� �Ǽ��� ���� �� �ִ�. ���õ� ��� ��ȯ ����: %lf "
    ,"������ �� �ϳ��� �Ǽ��� ���� �� �ִ�. ���õ� ��� ��ȯ ����: %lf "
    ,"�Է� ���ڵ��� ��ĵ�Ͽ� ���ϴ� ������ �����͸� ������ ������ �� �ִ�. *���ǻ���: ���ڿ� ��ȯ���ڸ� ������ ������ �տ� &�� �ٿ��� ���������� �۵��Ѵ�. ���� ���⸦ �� �� �� ������ �ν����� ���Ѵ� "
    ,"����, ����, ������, ����, �������� ����ϴ� ������ "
    ,"������ ���� �����ϴ� ������ "
    ,"������ ���� 1�� ������Ű�ų� ���ҽ�ų �� �ִ�. ������ �տ� ������ ��� ����, �ڿ� ������ ��� �Ŀ� �������� �����Ų��"
    ,"��ũ��, �۴�, ũ�ų� ����, �۰ų� ����, ����, ���� �ʴ١� �� ���� ���� ���� ���踦 ����Ѵ�. ��ǻ�ʹ� ��0���� ����, ��0���� ������ ��� ���� ���̶�� �Ǵ��Ѵ�.(���� ���� ǥ�÷Ρ�1���� ���� �Ѵ�) "
    ,"���տ��� ���̴� ������, ������, �����ո� ���ϸ� ���� ������ �Ǵ��ϴµ� ���̴� ������ "
    ,"�ǿ������� ũ�⸦ ����Ʈ ������ ����ؼ� �˷��� �� �ִ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"���ǽ��� ���� �� ���๮ ����, �����̸� �ƹ��͵� �������� ����. "
    ,"���ǽ�1�� ���̸� ���๮1�� ����, ���ǽ�2�� ���̸� ���๮2�� ������"
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ while���� �ٸ��� ������ ������ �Ȱ���. ��Ȯ�� ���ڸ� �ݺ��ϱ⿡ �����ϴ�. "
    ,"Ư���ϰ� ���๮�� ������ ������ �� ���ǿ� ������ �ݺ��� �Ǵ� �ݺ������� ������ �� ���� ����Ǿ�� �Ѵٸ� �ش� �ݺ����� ���� �� ȿ�����̴�. "
    ,"�Լ��� ���¸� �˸���, ��ǻ�Ͱ� �Լ��� ���縦 �ν��� �� �ֵ��� �ڵ� ó���� �Լ� ������ �� ���´�.  "
    ,"�ش� �Լ��� ����� �����Ѵ�. ���� ���� �ڵ� �տ� ���� �Լ������� �ϴ� �������� ���ش�. "
    ,"�Լ��� ����ϴ� ��ɾ�� �Լ��� �ʿ��� ���� �μ��� �ش�. "
    ,"�� ������ �Ϸ��� �������� ���� ���, ȿ������ ���� ����ϰ� �Ѵ�. *���� ����: ������ ��Ҵ� 0~N-1�̴�. 2����,3���� �迭�� �ִ�. "
    ,"Scanf�� ���� ���ڿ��� ���� �� ������ ���⸦ �ϸ� �ڴ� ������ �ʴ� Scanf�� �޸� Enter�������� ��� ���ڿ��� �� ����ȴ�. ������ �Է��� �迭�� ũ�⸦ �˻����� �ʱ� ������ ������ ���� ���� ������ �����ؾ��Ѵ�. "
    ,"Printf�� ���� ����� ���������� ��� �� �������� ���� �ٲ�����ϴ� printf�� �޸� �ڵ����� ���� �ٲ��ش�.  "
    ,"NULL"
    ,"���ڿ�2�� ���ڿ�1�� �����Ѵ�. "
    ,"���ڿ��� ����(���ڼ�)�� ���� ��ȯ��Ų��. "
    ,"���ڿ�2���ٰ� ���ڿ�1�� �̾���� "
    ,"���ڿ�1�� ���ڿ�2���� ũ�� 1��ȯ�ϰ� ���ڿ�1�� ���ڿ�2���� ������ -1��ȯ, ���� ���� ���ڿ��̸� 0��ȯ�Ѵ�. "
    ,"���������� ������ ���������� ����� �� �ִ� ������ ���մϴ�. �׷��� ������ �̸��� ���Ƶ� ����� �Լ��� �ٸ��ٸ� ���� ������ ��������� �����ϴ�. �޸𸮸� ȿ�������� ��� �����ϸ� ����뿡 �����ϱ� ������ ����մϴ�. "
    ,"�ڵ��� ��� �Լ� ���ܿ��� ����� �����մϴ�. �׷��� ������ ���� �Լ����� ���� ���������ϴٴ� ������ ������ �뷮�� ���� ����ϸ� ���������� ���� �߸��ȴٸ� ���� ������ ���� ��� �Լ��� ���ľ� �Ѵٴ� ������ �ֽ��ϴ�. "
    ,"���α׷��� ����� ���ȿ� ��� �����ǹǷν� �Լ��� ������ �ʱ�ȭ�Ǵ� ���������� ���̰� �ִ�. "
    };
    int q = 1;
    for (int p = 0; p < N; p++) {
        printf("\n%d.%s", q, list1[p]);
        q++;
        printf("\n:");
        printf("%s\n", list3[p]);
        printf("����: %s\n", list2[p]);
    }
}


int memorize() {
    int b = 0;
    printf("���⼭���ʹ� '�ϱ��' �ܾ����Դϴ�.\n");
    printf("��� ���������� ������ '1', ���� ���������� ������ '2'�� �����ּ���.\n");
    scanf("%d", &b);
    char list1[N][20] = { "��ó��", "������","��ũ" "�Լ�","printf ","Stdio.h", " �����","���","����","int",
 "double","char","Scanf","���������","���Կ�����","����������","���迬����","��������","sizeof������","���ǿ�����",
 "if��","if~else��", "If~else if~else��","Switch~case��","while��", "�Լ� ����","�Լ� ����","�Լ� ȣ��","�迭", "gets",
 "for��","do~while��","gets", "puts",  "������","strcpy","strlen","strcat", "strcmp","��������",
 "��������","������������" };//42��

    char list2[N][100] = { "NULL","NULL","NULL","NULL",  "printf(��  ��);" , "Include <stdio.h> ","NULL", "Ex. �¾ �ð�(���), �������� �θ�� ",  "Ex. ����, Ű, ������",
    "int age; ","double height; ", "char food; ", "scanf(��%d��, &a); ", "c=a+b;,c=a-b;c=a/b;, c=a*b; c=a%b; ", "=  ",
    "++a;, b++;, --c;, d--; ", "a>b;, a<b;, a>=b;, a<=b;, a==b;, a!=b; ","(a>10)&&(a>7);,(a>10)||(a>7);,!(a>10); ",
     "sizeof(������ �Ǵ� �ڷ���) ","(����) ? (���� ��) : (������ ��);", "If(���ǽ�) ���๮; ", "if(���ǹ�) ���๮1; else ���๮2; ",
    " else if (���ǹ�2) ���๮2;else ���๮; ", "switch(���ǽ�){ case�����1; ���๮; break;case �����2; ���๮; break;default; ���๮; break; } ",
     "while(���ǽ�){ ���๮; } ", "������ �Լ���(������,1 ������2); ", "������ �Լ� �̸�(������1,������2){���; reture ��ȯ��;} ",
    "�Լ��̸�(������3,������4) ; ", "�ڷ��� �迭��[N]={��1,��2,��3.....��N}; ","for(�ʱ��; ���ǽ�; ������){ ���๮; } ",
    "Do{���๮; }while (���ǽ�); ",  "gets(�迭��); ","puts(�迭��); ", "������ *�����͸�=&������ ",
    "Strcpy(���ڿ�1,���ڿ�2); ","Strlen(���ڿ�); ", "Strcat(���ڿ�1, ���ڿ�2); ",  "strcmp (���ڿ�1, ���ڿ�2); ",
     "�Լ� �ȿ��� ���� ���� ", "�Լ��ۿ��� ���� ���� ","static ������ ������;  " };

    char list3[N][250] = {
     "��ó�� �����ڿ� ���� �ҽ������� �����ϴ� ����"
    ,"CPU�� �ؼ��� �� �ִ� ��ɾ��� ������ ��ü���Ϸ� �ٲٴ� ���� "
    ,"��ü���Ͽ� startup code�� �����ϴ� ���� "
    ,"�Ӹ�(�Լ� ����)�� �������� �����Ǿ� �ִ�. "
    ,"ȭ�鿡 �����͸� ������ ���Ŀ� ���� ����� �� �ִ�."
    ,"C���� �⺻���� ����ϴ� ����� �Լ��� �� �ִ�."
    ,"NULL"
    ,"���� ������ �ʴ� ������ "
    ,"���� �ٲ�� ������ "
    ,"������ �� �ϳ��� ������ ���� �� �ִ�. ���õ� ��� ��ȯ ����: %d "
    ,"������ �� �ϳ��� �Ǽ��� ���� �� �ִ�. ���õ� ��� ��ȯ ����: %lf "
    ,"������ �� �ϳ��� �Ǽ��� ���� �� �ִ�. ���õ� ��� ��ȯ ����: %lf "
    ,"�Է� ���ڵ��� ��ĵ�Ͽ� ���ϴ� ������ �����͸� ������ ������ �� �ִ�. *���ǻ���: ���ڿ� ��ȯ���ڸ� ������ ������ �տ� &�� �ٿ��� ���������� �۵��Ѵ�. ���� ���⸦ �� �� �� ������ �ν����� ���Ѵ� "
    ,"����, ����, ������, ����, �������� ����ϴ� ������ "
    ,"������ ���� �����ϴ� ������ "
    ,"������ ���� 1�� ������Ű�ų� ���ҽ�ų �� �ִ�. ������ �տ� ������ ��� ����, �ڿ� ������ ��� �Ŀ� �������� �����Ų��"
    ,"��ũ��, �۴�, ũ�ų� ����, �۰ų� ����, ����, ���� �ʴ١� �� ���� ���� ���� ���踦 ����Ѵ�. ��ǻ�ʹ� ��0���� ����, ��0���� ������ ��� ���� ���̶�� �Ǵ��Ѵ�.(���� ���� ǥ�÷Ρ�1���� ���� �Ѵ�) "
    ,"���տ��� ���̴� ������, ������, �����ո� ���ϸ� ���� ������ �Ǵ��ϴµ� ���̴� ������ "
    ,"�ǿ������� ũ�⸦ ����Ʈ ������ ����ؼ� �˷��� �� �ִ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"���ǽ��� ���� �� ���๮ ����, �����̸� �ƹ��͵� �������� ����. "
    ,"���ǽ�1�� ���̸� ���๮1�� ����, ���ǽ�2�� ���̸� ���๮2�� ������"
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ ���̳� �����̳Ŀ� ���� �ٸ� ����� �����ϵ��� �ϴ� ������ "
    ,"������ while���� �ٸ��� ������ ������ �Ȱ���. ��Ȯ�� ���ڸ� �ݺ��ϱ⿡ �����ϴ�. "
    ,"Ư���ϰ� ���๮�� ������ ������ �� ���ǿ� ������ �ݺ��� �Ǵ� �ݺ������� ������ �� ���� ����Ǿ�� �Ѵٸ� �ش� �ݺ����� ���� �� ȿ�����̴�. "
    ,"�Լ��� ���¸� �˸���, ��ǻ�Ͱ� �Լ��� ���縦 �ν��� �� �ֵ��� �ڵ� ó���� �Լ� ������ �� ���´�.  "
    ,"�ش� �Լ��� ����� �����Ѵ�. ���� ���� �ڵ� �տ� ���� �Լ������� �ϴ� �������� ���ش�. "
    ,"�Լ��� ����ϴ� ��ɾ�� �Լ��� �ʿ��� ���� �μ��� �ش�. "
    ,"�� ������ �Ϸ��� �������� ���� ���, ȿ������ ���� ����ϰ� �Ѵ�. *���� ����: ������ ��Ҵ� 0~N-1�̴�. 2����,3���� �迭�� �ִ�. "
    ,"Scanf�� ���� ���ڿ��� ���� �� ������ ���⸦ �ϸ� �ڴ� ������ �ʴ� Scanf�� �޸� Enter�������� ��� ���ڿ��� �� ����ȴ�. ������ �Է��� �迭�� ũ�⸦ �˻����� �ʱ� ������ ������ ���� ���� ������ �����ؾ��Ѵ�. "
    ,"Printf�� ���� ����� ���������� ��� �� �������� ���� �ٲ�����ϴ� printf�� �޸� �ڵ����� ���� �ٲ��ش�.  "
    ,"NULL"
    ,"���ڿ�2�� ���ڿ�1�� �����Ѵ�. "
    ,"���ڿ��� ����(���ڼ�)�� ���� ��ȯ��Ų��. "
    ,"���ڿ�2���ٰ� ���ڿ�1�� �̾���� "
    ,"���ڿ�1�� ���ڿ�2���� ũ�� 1��ȯ�ϰ� ���ڿ�1�� ���ڿ�2���� ������ -1��ȯ, ���� ���� ���ڿ��̸� 0��ȯ�Ѵ�. "
    ,"���������� ������ ���������� ����� �� �ִ� ������ ���մϴ�. �׷��� ������ �̸��� ���Ƶ� ����� �Լ��� �ٸ��ٸ� ���� ������ ��������� �����ϴ�. �޸𸮸� ȿ�������� ��� �����ϸ� ����뿡 �����ϱ� ������ ����մϴ�. "
    ,"�ڵ��� ��� �Լ� ���ܿ��� ����� �����մϴ�. �׷��� ������ ���� �Լ����� ���� ���������ϴٴ� ������ ������ �뷮�� ���� ����ϸ� ���������� ���� �߸��ȴٸ� ���� ������ ���� ��� �Լ��� ���ľ� �Ѵٴ� ������ �ֽ��ϴ�. "
    ,"���α׷��� ����� ���ȿ� ��� �����ǹǷν� �Լ��� ������ �ʱ�ȭ�Ǵ� ���������� ���̰� �ִ�. "
    };


    if (b == 1) {//��� ������
        for (int p = 0, q = 1; p < 41; p++, q++) {
            printf("\n%d. ??? \n", q);
            printf(":%s\n", list3[p]);
        }
        /*srand((unsigned int)time(NULL));
        int k1[N] = { NULL };
        int n = 100;//100�� �ǹ̾��� ����
        n = (rand() % N) + 1;
        int g = 0;
        while (1) {
           if (k1[g] != n) {
              k1[g] = n;
              g++;
           }
           else {
              n//�ߺ��� n�� �ƿ� ���ܽ�Ű�ŽäФ���

           }*/




    }
    else if (b == 2) {//���� ������
        for (int p = 0, q = 1; p < N; p++, q++) {
            printf("\n%d.%s\n", q, list1[p]);
            printf("����: ???\n");
        }
    }
    else {
        while (1) {
            printf("'1'�Ǵ� '2' �� �߿� �ϳ��� ����ֽʽÿ�.\n");
            scanf(" %d", &b);

        }
    }
}