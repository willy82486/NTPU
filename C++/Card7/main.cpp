#include "Card.h"

int main(int argc,char **argv)
{
    while(1){
        fstream check("Card.txt",ios::in);
        fstream secretcheck("secret.txt",ios::in);
        if(!check||!secretcheck){
            cerr<<"File can not be opened"<<endl;
            exit(1);
        }
        char ch,sch;
        check.get(ch);
        secretcheck.get(sch);
        if(check.eof()||secretcheck.eof()){//-----------------------------------------------------------------space
            int n;
            cout<<"How many people you want to play(2-52)(include you)?"<<endl;
            cin>>n;
            while(cin.fail()){
                cin.clear();
                cin.ignore();
                cin>>n;
            }
            while(n<2||n>52){
            cout<<"How many people you want to play(2-52)(include you)?"<<endl;
            cin>>n;
            while(cin.fail()){
                cin.clear();
                cin.ignore();
                cin>>n;
            }
        }
            system("cls");
            Card a(n);
            cout<<endl<<endl<<endl;
            cout<<"New Game!!!"<<endl;
            system("pause");
            system("cls");
        }
        else{//----------------------------------------------------------------------------not space
            int answer;
            cout<<"Do you want to continue playing the last game ?(input 1 or 0)(1 -->Yes  0-->No)"<<endl;
            cin>>answer;
            while(cin.fail()){
                cin.clear();
                cin.ignore();
                cin>>answer;
            }
            while(answer!=1&&answer!=0){
                cin>>answer;
                while(cin.fail()){
                cin.clear();
                cin.ignore();
                cin>>answer;
                }
            }
            system("cls");


            if(answer==1){
                Card b;
                cout<<endl<<endl<<endl;
                fstream file("Card.txt",ios::out);
                fstream secret("secret.txt",ios::out);
                if(!file||!secret)
                {
                    cerr << "Can't open file!\n";
                    exit(1);
                }
                file.close();
                secret.close();
                cout<<"New Game!!!"<<endl;
                system("pause");
                system("cls");
            }
            else{
                fstream file("Card.txt",ios::out);
                fstream secret("secret.txt",ios::out);
                if(!file||!secret)
                {
                    cerr << "Can't open file!\n";
                    exit(1);
                }
                file.close();
                secret.close();
                int n;
                cout<<"How many people you want to play(2-52)(include you)?"<<endl;
                cin>>n;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cin>>n;
                }
                while(n<2||n>52){
                    cout<<"How many people you want to play(2-52)(include you)?"<<endl;
                    cin>>n;
                    while(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cin>>n;
                    }
                }
                system("cls");
                Card a(n);
                cout<<endl<<endl<<endl;
                cout<<"New Game!!!"<<endl;
                system("pause");
                system("cls");
            }
        }
        check.close();
        secretcheck.close();
    }
    return 0;
}

