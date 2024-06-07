#include <iostream>
using namespace std;

void AppendText();
void NewLine();
void SaveTo();
void LoadFrom();
void CurrentText();
void InsertText();
void Search();
void Delete();
void Copy();
void Cut();
void Paste();
void Undo();
void Redo();
void Replace();

FILE *techFile;
FILE *savingFile;
FILE *loadingFile;

int main()
{
    cout<<"Hello, World!\n";

    techFile = fopen("file.txt", "w");
    fclose(techFile);

    cout<<"1 - Append text symbols to the end \n"
        <<"2 - Start the new line \n"
        <<"3 - Use files to saving the information \n"
        <<"4 - Use files to loading the information \n"
        <<"5 - Print the current text to console \n"
        <<"6 - Insert the text by line and symbol index \n"
        <<"7 - Search \n"
        <<"8 - Delete \n"
        <<"9 - Copy \n"
        <<"10 - Cut \n"
        <<"11 - Paste \n"
        <<"12 - Undo \n"
        <<"13 - Redo \n"
        <<"14 - Replace \n"
        <<"15 - exit \n";


    int optionNumber;
    while (true) {
        cout<<"Please, choose the command\n";
        cin>>optionNumber;

        switch (optionNumber) {
            case 1:
                AppendText();
                break;
            case 2:
                NewLine();
                break;
            case 3:
                SaveTo();
                break;
            case 4:
                LoadFrom();
                break;
            case 5:
                CurrentText();
                break;
            case 6:
                InsertText();
                break;
            case 7:
                Search();
                break;
            case 8:
                Delete();
                break;
            case 9:
                Copy();
                break;
            case 10:
                Cut();
                break;
            case 11:
                Paste();
                break;
            case 12:
                Undo();
                break;
            case 13:
                Redo();
                break;
            case 14:
                Replace();
                break;
            case 15:
                return 0;
            default:
                cout<<"The command is not implemented\n";
                break;
        }
    }
    return 0;
}


void AppendText() {
    cout<<"Enter text to append: \n";
    techFile = fopen("file.txt", "a");
    char userInput;
    getchar();
    while(true) {
        userInput = getchar();
        if (userInput == '\n') {
            break;
        }
        fprintf(techFile, "%c", userInput);
    }
    fclose(techFile);
}

void NewLine() {
    cout<<"New line is started \n";
    techFile = fopen("file.txt", "a");
    fprintf(techFile, "\n");
    fclose(techFile);
}

void SaveTo() {
    cout<<"Enter the file name for saving (not more 20 symbols): \n";
    char filePath[21];
    cin>>filePath;

    savingFile = fopen(filePath, "a");
    techFile = fopen("file.txt", "r");
    char symbol;
    while (true) {
        symbol = fgetc(techFile);
        if (symbol == EOF) {
            break;
        }
        fputc(symbol, savingFile);
    }
    fclose(savingFile);
    fclose(techFile);

    techFile = fopen("file.txt", "w"); // просто очистити файл
    fclose(techFile);
}

void LoadFrom() {
    cout<<"Enter the file name for loading: \n";
    char filePath[21];
    cin>>filePath;
    techFile = fopen("file.txt", "a");
    loadingFile = fopen(filePath, "r");
    char symbol;
    while (true) {
        symbol = fgetc(loadingFile);
        if (symbol == EOF) {
            break;
        }
        fputc(symbol, techFile);
    }
    fclose(loadingFile);
    fclose(techFile);
}

void CurrentText() {
    techFile = fopen("file.txt", "r");
    char c;
    while ((c = getc(techFile)) != EOF) {
        cout<<c;
    }
    cout<<endl;
    fclose(techFile);
}

void InsertText() {
    cout<<"Choose line and index to insert text: \n";
    int line;
    int index;
    cin>>line>>index;
    getchar();

    techFile = fopen("file.txt", "r");
    long fileSize = 0;
    char symbol;
    while ((symbol = fgetc(techFile)) != EOF) {
        fileSize++;
    }
    fclose(techFile);

    char *fileContent = (char *) malloc((fileSize+1) * sizeof(char));
    techFile = fopen("file.txt", "r");
    fread(fileContent, 1, fileSize, techFile);
    fileContent[fileSize] = '\0';
    fclose(techFile);

    int lineCounter = 0;
    int indexCounter = 0;
    int counter1 = 0;
    while (fileContent[counter1] != '\0') {
        if (lineCounter == line && indexCounter == index) {
            break;
        }
        if (fileContent[counter1] == '\n') {
            lineCounter++;
            indexCounter = 0;
        } else {
            indexCounter++;
        }
        counter1++;
    }

    cout<<"Enter the text to insert: \n";
    char *userInput = (char *) malloc(100 * sizeof(char));
    fgets(userInput, 100, stdin);
    int userInputSize = strlen(userInput);

    if (userInput[userInputSize - 1] == '\n') {  // треба бо вставе \n після вводу
        userInput[userInputSize - 1] = '\0';
        userInputSize--;
    }

    int newFileSize = fileSize + userInputSize;
    char *newFileContent = (char *)malloc((newFileSize + 1) * sizeof(char));
    int counter2 = 0;
    for (int i = 0; i < counter1; i++) {
        newFileContent[counter2] = fileContent[i];
        counter2++;
    }
    for (int i = 0; i < userInputSize; i++) {
        newFileContent[counter2] = userInput[i];
        counter2++;
    }
    for (int i = counter1; i < fileSize; i++) {
        newFileContent[counter2] = fileContent[i];
        counter2++;
    }
    newFileContent[newFileSize] = '\0';

    techFile = fopen("file.txt", "w");
    fputs(newFileContent, techFile);
    fclose(techFile);

    free(fileContent);
    free(userInput);
    free(newFileContent);
}

void Search() {
    cout<<"Enter the text to search: \n";
    getchar();
    char *searchText = (char *) malloc(100 * sizeof(char));
    fgets(searchText, 100, stdin);
    int lenInput = strlen(searchText);
    if (searchText[lenInput - 1] == '\n') {
        searchText[lenInput - 1] = '\0';
        lenInput--;
    }

    techFile = fopen("file.txt", "r");
    long fileSize = 0;
    char symbol;
    while ((symbol = fgetc(techFile)) != EOF) {
        fileSize++;
    }
    fclose(techFile);

    techFile = fopen("file.txt", "r");
    char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));

    fread(fileContent, 1, fileSize, techFile);
    fileContent[fileSize] = '\0';

    char *lineBuffer = (char *) malloc(100 * sizeof(char));
    int lineNumber = 0;
    int currentIndex = 0;
    char *pos = strstr(fileContent, searchText);
    if (pos != NULL) {
        int index = pos - fileContent;
        for (int i = 0; i < index; i++) {
            if (fileContent[i] == '\n') {
                lineNumber++;
                currentIndex = 0;
            }
            currentIndex++;
        }
        cout<<lineNumber + 1<<currentIndex + 1<<endl;
    }

    free(searchText);
    free(fileContent);
    free(lineBuffer);
    fclose(techFile);
}
