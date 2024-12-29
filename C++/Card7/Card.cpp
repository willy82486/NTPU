#include "Card.h"

bool comp(pair<int,int> a,pair<int,int> b){
	if(a.first==b.first){
		return a.second<b.second;
	}
	return a.first<b.first;
}
bool comp2(pair<int,int> a,pair<int,int> b){
	if(a.second==b.second){
		return a.first<b.first;
	}
	return a.second<b.second;
}
//---------------------------------------------------------------------------------------------------------
void Card::SetColor(int color){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}
//---------------------------------------------------------------------------------------------------------

Card::Card(int playerNum){
    srand(time(NULL));
    //-----------------------------------------------------------------------------------------------------
    PlayerNum=playerNum;
    //-----------------------------------------------------------------------------------------------------
    memset(total,0,sizeof(total));
    //-----------------------------------------------------------------------------------------------------
    Suit["Spade"]=1;
    Suit["Heart"]=2;
    Suit["Diamond"]=3;
    Suit["Club"]=4;
    //-----------------------------------------------------------------------------------------------------
    memset(field,0,sizeof(field));
    //-----------------------------------------------------------------------------------------------------
    for(int i=0;i<13;i++){
        NumberOfCard.push_back(make_pair(1,i%13+1));
    }
    for(int i=13;i<26;i++){
        NumberOfCard.push_back(make_pair(2,i%13+1));
    }
    for(int i=26;i<39;i++){
        NumberOfCard.push_back(make_pair(3,i%13+1));
    }
    for(int i=39;i<52;i++){
        NumberOfCard.push_back(make_pair(4,i%13+1));
    }
    //------------------------------------------------------------------------
    /*for(int i=0;i<52;i++){
        int j=rand()%52;
        swap(NumberOfCard[i],NumberOfCard[j]);
    }*/

    random_shuffle(NumberOfCard.begin(),NumberOfCard.end());
    //------------------------------------------------------------------------
    for(int i=0;i<52;i++){
        player[i%PlayerNum].push_back(NumberOfCard[i]);
    }
    //------------------------------------------------------------------------
    Run();
    //------------------------------------------------------------------------
}

Card::Card(){
    checkflag=0;
    Suit["Spade"]=1;
    Suit["Heart"]=2;
    Suit["Diamond"]=3;
    Suit["Club"]=4;
    memset(field,0,sizeof(field));
    memset(total,0,sizeof(total));
    read();
    if(checkflag==1){
    }
    else{
        Run();
    }
}

bool Card::Deal(int num_player){
    for(unsigned int i=0;i<player[num_player].size();i++){
        if(player[num_player][i].second>7){//---------------------------------------------------------7
            for(int k=0;k<4;k++){
                if(player[num_player][i].first==k+1&&player[num_player][i].second==(field[0][k]+1)){
                    canthrow[num_player].push_back(make_pair(k+1,(field[0][k]+1)));
                    break;
                }
            }
            fold[num_player].push_back(make_pair(player[num_player][i].first,player[num_player][i].second));
        }

        else if(player[num_player][i].second<7){ //---------------------------------------------------7
            for(int k=0;k<4;k++){
                if(player[num_player][i].first==k+1&&player[num_player][i].second==(field[2][k]-1)){
                    canthrow[num_player].push_back(make_pair(k+1,(field[2][k]-1)));
                    break;
                }
            }
            fold[num_player].push_back(make_pair(player[num_player][i].first,player[num_player][i].second));
        }

        else {//--------------------------------------------------------------------------------------单7
            for(int k=0;k<4;k++){
                if(player[num_player][i].first==k+1&&field[1][k]==0){
                    canthrow[num_player].push_back(make_pair(k+1,7));
                    break;
                }
            }
        }
        //------------------------------------------------------------------------------------------------
    }
    //----------------------------------------------------------------------------------------------------
    if(!canthrow[num_player].empty()){
        /*sort(canthrow[num_player].begin(),canthrow[num_player].end(),comp);*/
        random_shuffle(canthrow[num_player].begin(),canthrow[num_player].end());
        return true;
    }
    else{
        sort(fold[num_player].begin(),fold[num_player].end(),comp2);
        return false;
    }
}

void Card::Run(){//----------------------------------------------------------------------------------主程式
    while(!player[0].empty()){
    //*----------------------------------------------------------------------------------------------still have card
        if(field[1][0]==0){//------------------------------------------------------------------------find Spade7
            int flag=0;
            int Spade7is=0;
            for(int i=0;i<PlayerNum;i++){
                for(unsigned int index=0;index<player[i].size();index++){
                    if((player[i][index].first)==1&&(player[i][index].second)==7){
                        field[0][(player[i][index].first)-1]=7;
                        field[1][(player[i][index].first)-1]=7;
                        field[2][(player[i][index].first)-1]=7;
                        player[i].erase(player[i].begin()+index);
                        Spade7is=i;
                        flag=1;

                        if(i==0){
                            cout<<"Player sents Spade 7"<<endl;
                        }
                        else{
                            cout<<"Computer "<<i<< " sends "<<"Spade "<<"7"<<endl;
                        }

                        break;
                    }
                }
                if(flag==1){
                    break;
                }
            }

            for(int i=Spade7is+1;i<PlayerNum;i++){//---------------------------------------------------after finding Spade7
                if(Deal(i)){
                        cout<<"Computer "<<i<< " sends "<<Asuit[canthrow[i][0].first]<<" "<<canthrow[i][0].second<<endl;
                        if(canthrow[i][0].second>7){
                            field[0][canthrow[i][0].first-1]=canthrow[i][0].second;
                        }
                        else if(canthrow[i][0].second<7){
                            field[2][canthrow[i][0].first-1]=canthrow[i][0].second;
                        }
                        else{
                            field[1][canthrow[i][0].first-1]=canthrow[i][0].second;
                            field[0][canthrow[i][0].first-1]=canthrow[i][0].second;
                            field[2][canthrow[i][0].first-1]=canthrow[i][0].second;
                        }
                        for(unsigned int index=0;index<player[i].size();index++){
                            if((player[i][index].first)==canthrow[i][0].first&&(player[i][index].second)==canthrow[i][0].second){
                                player[i].erase(player[i].begin()+index);
                            }
                        }
                        canthrow[i].erase(canthrow[i].begin(),canthrow[i].end());
                        fold[i].erase(fold[i].begin(),fold[i].end());
                }
                else{
                        cout<<"Computer "<<i<< " folds "/*<<Asuit[fold[i][0].first]<<" "<<fold[i][0].second*/<<endl;
                        for(unsigned int index=0;index<player[i].size();index++){
                            if((player[i][index].first)==fold[i][0].first&&(player[i][index].second)==fold[i][0].second){
                                total[i]=total[i]+fold[i][0].second;
                                player[i].erase(player[i].begin()+index);
                            }
                        }
                        canthrow[i].erase(canthrow[i].begin(),canthrow[i].end());
                        fold[i].erase(fold[i].begin(),fold[i].end());
                }
            }
        }
    //*------------------------------------------------------------------------------------------second round
        else{
        //--------------------------------------------------------------------------------------------------------------save file
            fstream file("Card.txt",ios::out);
            fstream secret("secret.txt",ios::out);
            if(!file||!secret)
            {
                cerr << "Can't open file!\n";
                exit(1);
            }
            file<<PlayerNum<<endl;
            secret<<(PlayerNum+CODE2)*CODE<<endl;
            for(int i=0;i<PlayerNum;i++){
                for(int j=0;j<player[i].size();j++){
                    file<<player[i][j].first<<" "<<player[i][j].second;
                    secret<<(player[i][j].first+CODE2)*CODE<<" "<<(player[i][j].second+CODE2)*CODE;
                    if(j==player[i].size()-1){
                        continue;
                    }
                    else{
                        file<<" ";
                        secret<<" ";
                    }
                }
                file<<endl;
                secret<<endl;
            }
            for(int i=0;i<3;i++){
                for(int j=0;j<4;j++){
                    file<<field[i][j];
                    secret<<(field[i][j]+CODE2)*CODE;
                    if(j==3){
                        file<<endl;
                        secret<<endl;
                    }
                    else{
                        file<<" ";
                        secret<<" ";
                    }
                }
            }
            for(int i=0;i<PlayerNum;i++){
                file<<total[i]<<endl;
                secret<<(total[i]+CODE2)*CODE<<endl;
            }
            file.close();
            secret.close();
            //--------------------------------------------------------------------------------------------------------------
            string a;
            int b;
            if(Deal(0)){//----------------------------------------------------------------------------Human
                cout<<"player sends(Suit:Spade,Heart,Diamond,Club) OR input 0 to end game :"<<endl;
                while(1){
                    cin>>a;
                    if(a=="0"){
                        system("TASKKILL /F /IM 410785018Card7.exe ");
                    }
                    cout<<"(Number:1-13) OR input 0 to end game :"<<endl;
                    cin>>b;
                    while(cin.fail()){
                        cin.clear();
                        cin.ignore();
                        cin>>b;
                    }
                    if(b==0){
                        system("TASKKILL /F /IM 410785018Card7.exe");
                    }
                    pair<int,int> tmp(Suit[a],b);
                    if(ChooseCard(0,tmp)){
                        system("cls");
                        cout<<"player sends "<<a<<" "<<b<<endl;
                        break;
                    }
                    else{
                        cout<<"You cannot send that card !"<<endl;
                        cout<<"player sends(Suit:Spade,Heart,Diamond,Club) :"<<endl;
                    }
                }
                canthrow[0].erase(canthrow[0].begin(),canthrow[0].end());
            }
            else{
                cout<<"player folds(Suit:Spade,Heart,Diamond,Club) OR input 0 to end game "<<endl;
                while(1){
                    cin>>a;
                    if(a=="0"){
                        system("TASKKILL /F /IM 410785018Card7.exe ");
                    }
                    cout<<"(Number:1-13) OR input 0 to end game  :"<<endl;
                    cin>>b;
                     while(cin.fail()){
                        cin.clear();
                        cin.ignore();
                        cin>>b;
                    }
                    if(b==0){
                        system("TASKKILL /F /IM 410785018Card7.exe ");
                    }
                    pair<int,int> tmp(Suit[a],b);
                    if(FoldCard(0,tmp)){
                        system("cls");
                        break;
                    }
                    else{
                        cout<<"You cannot fold that card !"<<endl;
                        cout<<"player folds(Suit:Spade,Heart,Diamond,Club) :"<<endl;
                    }
                }

                fold[0].erase(fold[0].begin(),fold[0].end());
            }
        //-----------------------------------------------------------------------------------------Computer
            for(int i=1;i<PlayerNum;i++){
                if(!player[i].empty()){
                    if(Deal(i)){
                            cout<<"Computer "<<i<< " sends "<<Asuit[canthrow[i][0].first]<<" "<<canthrow[i][0].second<<endl;
                            if(canthrow[i][0].second>7){
                                field[0][canthrow[i][0].first-1]=canthrow[i][0].second;
                            }
                            else if(canthrow[i][0].second<7){
                                field[2][canthrow[i][0].first-1]=canthrow[i][0].second;
                            }
                            else{
                                field[1][canthrow[i][0].first-1]=canthrow[i][0].second;
                                field[0][canthrow[i][0].first-1]=canthrow[i][0].second;
                                field[2][canthrow[i][0].first-1]=canthrow[i][0].second;
                            }
                            for(unsigned int index=0;index<player[i].size();index++){
                                if((player[i][index].first)==canthrow[i][0].first&&(player[i][index].second)==canthrow[i][0].second){
                                    player[i].erase(player[i].begin()+index);
                                }
                            }
                            canthrow[i].erase(canthrow[i].begin(),canthrow[i].end());
                            fold[i].erase(fold[i].begin(),fold[i].end());
                    }
                    else{
                            cout<<"Computer "<<i<< " folds "/*<<Asuit[fold[i][0].first]<<" "<<fold[i][0].second*/<<endl;
                            for(unsigned int index=0;index<player[i].size();index++){
                                if((player[i][index].first)==fold[i][0].first&&(player[i][index].second)==fold[i][0].second){
                                    total[i]=total[i]+fold[i][0].second;
                                    player[i].erase(player[i].begin()+index);
                                }
                            }
                            canthrow[i].erase(canthrow[i].begin(),canthrow[i].end());
                            fold[i].erase(fold[i].begin(),fold[i].end());
                    }
                }
            }

        }
        cout<<"Card on the field :"<<endl;
        PrintField();
        sort(player[0].begin(),player[0].end(),comp);
        if(!player[0].empty()){
            cout<<"Card that you have :"<<endl;
            PrintHuman();
        }
    }
    //-----------------------------------------------------------------------------------------------------
    Finish();
}

bool Card::ChooseCard(int a,pair<int,int> b){
    for(unsigned int idx=0;idx<player[0].size();idx++){
        if(b.first==player[0][idx].first&&b.second==player[0][idx].second){
            if(b.second>7&&b.second==field[0][b.first-1]+1){
                field[0][b.first-1]=player[0][idx].second;
                player[0].erase(player[0].begin()+idx);
                return true;
                break;
            }
            //---------------------------------------------------------------------------------------------
            else if(b.second<7&&b.second==field[2][b.first-1]-1){
                field[2][b.first-1]=player[0][idx].second;
                player[0].erase(player[0].begin()+idx);
                return true;
                break;
            }

            //---------------------------------------------------------------------------------------------
            else if(b.second==7&&field[1][b.first-1]==0){
                field[1][b.first-1]=player[0][idx].second;
                field[0][b.first-1]=player[0][idx].second;
                field[2][b.first-1]=player[0][idx].second;
                player[0].erase(player[0].begin()+idx);
                return true;
                break;
            }
            else{
                return false;
                break;
            }
            //---------------------------------------------------------------------------------------------
        }
    }
    return false;
}

bool Card::FoldCard(int a,pair<int,int> b){
    for(unsigned int idx=0;idx<player[0].size();idx++){
            if(b.first==player[0][idx].first&&b.second==player[0][idx].second){
                total[a]=total[a]+b.second;
                player[0].erase(player[0].begin()+idx);
                return true;
                break;
            }
        }
        return false;
}

void Card::PrintHuman(){
    unsigned int linetotal=0;
    unsigned int linecount=0;
    unsigned int cardtotal=0;
    if(7<player[0].size()){
        linetotal=7;
    }
    else{
        linetotal=player[0].size();
    }
    //------------------------------------------------------------------------------------------------------
    while(cardtotal<player[0].size()){
        for(unsigned int i=0;i<linetotal;i++){
            if(player[0][i+7*linecount].first==2||player[0][i+7*linecount].first==3){
                SetColor(12);
                cout<<left<<setw(13)<<setfill('=')<<Number[player[0][i+7*linecount].second];
                cout<<right<<setw(2)<<Number[player[0][i+7*linecount].second]<<" ";
                SetColor(7);
            }
            else{
                cout<<left<<setw(13)<<setfill('=')<<Number[player[0][i+7*linecount].second];
                cout<<right<<setw(2)<<Number[player[0][i+7*linecount].second]<<" ";
            }
        }
        cout<<endl;
        //-------------------------------------------------------------------------------
        for(int line=0;line<9;line++){
            for(unsigned int i=0;i<linetotal;i++){
                    switch(player[0][i+7*linecount].first)
                    {
                    case 1:
                        cout<<Spade[line];
                        break;
                    case 2:
                        SetColor(12);
                        cout<<Heart[line];
                        SetColor(7);
                        break;
                    case 3:
                        SetColor(12);
                        cout<<Diamond[line];
                        SetColor(7);
                        break;
                    case 4:
                        cout<<Club[line];
                        break;
                    }
                    cout<<" ";
            }
             cout<<endl;
        }
        //-------------------------------------------------------------------------------
         for(unsigned int i=0;i<linetotal;i++){
            if(player[0][i+7*linecount].first==2||player[0][i+7*linecount].first==3){
                SetColor(12);
                cout<<left<<setw(13)<<setfill('=')<<Number[player[0][i+7*linecount].second];
                cout<<right<<setw(2)<<Number[player[0][i+7*linecount].second]<<" ";
                SetColor(7);
            }
             else{
                cout<<left<<setw(13)<<setfill('=')<<Number[player[0][i+7*linecount].second];
                cout<<right<<setw(2)<<Number[player[0][i+7*linecount].second]<<" ";
            }
        }
        cout<<endl;
    //-----------------------------------------------------------------------------------
        cardtotal+=linetotal;
        if(cardtotal+7<player[0].size()){
            linetotal=7;
            linecount++;
        }
        else{
        linetotal=player[0].size()-cardtotal;
        linecount++;
        }
    }
}

void Card::PrintField(){
    for(int ground=0;ground<3;ground++){
        for(unsigned int i=0;i<4;i++){
            //------------------------------------------------------------------
            if(field[ground][i]==0){
                cout<<"                ";
            }
            //-------------------------------------------------------------------
            else{
                if(ground==0&&field[ground][i]==7){
                    cout<<"                ";
                }
                else if(ground==2&&field[ground][i]==7){
                    cout<<"                ";
                }
                //-----------------------------------------------------------------------
                else{
                    if(i==1||i==2){
                        SetColor(12);
                        cout<<left<<setw(13)<<setfill('=')<<Number[field[ground][i]];
                        cout<<right<<setw(2)<<Number[field[ground][i]]<<" ";
                        SetColor(7);
                    }
                    else{
                        cout<<left<<setw(13)<<setfill('=')<<Number[field[ground][i]];
                        cout<<right<<setw(2)<<Number[field[ground][i]]<<" ";
                    }
                }
                //-------------------------------------------------------------------------
            }
            //---------------------------------------------------------------------
        }
        cout<<endl;
        //-------------------------------------------------------------------------------
        for(int line=0;line<9;line++){
            for(unsigned int i=0;i<4;i++){
                //-----------------------------------------------------------------------
                if(field[ground][i]==0){
                cout<<Space[line];
                }
                //------------------------------------------------------------------------
                else{
                    if(ground==0&&field[ground][i]==7){
                        cout<<Space[line];
                    }
                    else if(ground==2&&field[ground][i]==7){
                        cout<<Space[line];
                    }
                    //--------------------------------------------------------------------
                    else{
                        switch(i)
                        {
                        case 0:
                            cout<<Spade[line];
                            break;
                        case 1:
                            SetColor(12);
                            cout<<Heart[line];
                            SetColor(7);
                            break;
                        case 2:
                            SetColor(12);
                            cout<<Diamond[line];
                            SetColor(7);
                            break;
                        case 3:
                            cout<<Club[line];
                            break;
                        }
                    }
                    //-----------------------------------------------------------------------
                }
                //---------------------------------------------------------------------------
                    cout<<" ";
            }
             cout<<endl;
        }
        //-------------------------------------------------------------------------------
         for(unsigned int i=0;i<4;i++){
            //---------------------------------------------------------------------------
            if(field[ground][i]==0){
                cout<<"                ";
            }
            //---------------------------------------------------------------------------
            else{
                if(ground==0&&field[ground][i]==7){
                    cout<<"                ";
                }
                else if(ground==2&&field[ground][i]==7){
                    cout<<"                ";
                }
                //-----------------------------------------------------------------------
                else{
                    if(i==1||i==2){
                        SetColor(12);
                        cout<<left<<setw(13)<<setfill('=')<<Number[field[ground][i]];
                        cout<<right<<setw(2)<<Number[field[ground][i]]<<" ";
                        SetColor(7);
                    }
                     else{
                        cout<<left<<setw(13)<<setfill('=')<<Number[field[ground][i]];
                        cout<<right<<setw(2)<<Number[field[ground][i]]<<" ";
                    }
                }
                //------------------------------------------------------------------------
            }
            //----------------------------------------------------------------------------
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}
//----------------------------------------------------------------------------------------------
void Card::Finish(){
    for(int t=0;t<PlayerNum;t++){
        if(t==0){
            cout<<"Player has "<<total[t]<<" points"<<endl;
        }
        //--------------------------------------------------------------------------------------
        else{
            cout<<"Computer "<<t<<" has "<<total[t]<<" points"<<endl;
        }
        //--------------------------------------------------------------------------------------
    }

    cout<<endl<<endl<<endl;
    int min_num=total[0];
    int winner_num=0;
    for(int i=1;i<PlayerNum;i++){
        if(total[i]<min_num){
            min_num=total[i];
        }
    }
    for(int i=0;i<PlayerNum;i++){
        if(total[i]==min_num){
            if(i==0){
                cout<<"Player Win!!!"<<endl;
            }
            else{
                cout<<"Computer "<<i<<" Win!!!"<<endl;
            }
        }
    }
    fstream file("Card.txt",ios::out);
    fstream secret("secret.txt",ios::out);
    if(!file||!secret)
    {
        cerr << "Can't open file!\n";
        exit(1);
    }
    file.close();
    secret.close();
}

int Card::read(){
    fstream file("Card.txt",ios::in);
    fstream secret("secret.txt",ios::in);
    if(!file||!secret)
    {
        cerr << "Can't open file!\n";
        exit(1);
    }
    string line,sline;
    int substring,ssubstring;
    stringstream token,stoken;
    //-------------------------------------------------
    getline(file,line);
    token.str(line);

    getline(secret,sline);
    stoken.str(sline);
    //-------------------------------------------------PlayerNum
    while(token>>substring){
        PlayerNum=substring;
    }

    while(stoken>>ssubstring){
        if(ssubstring/CODE-CODE2!= PlayerNum){
            ERR(1);
            file.close();
            secret.close();
            return 0;
        }
    }


    //-------------------------------------------------Card
    for(int i=0;i<PlayerNum;i++){
        token.str("");
        token.clear();
        getline(file,line);
        token.str(line);
        int a,b;
        int flag=1;
        while(token>>substring){
            if(flag==1){
                a=substring;
                flag=2;
            }
            else{
                b=substring;
                player[i].push_back(make_pair(a,b));
                flag=1;
            }
        }
    }

    for(int i=0;i<PlayerNum;i++){
        stoken.str("");
        stoken.clear();
        getline(secret,sline);
        stoken.str(sline);
        int a,b;
        int flag=1;
        while(stoken>>ssubstring){
            if(flag==1){
                a=ssubstring/CODE-CODE2;
                flag=2;
            }
            else{
                b=ssubstring/CODE-CODE2;
                secretplayer[i].push_back(make_pair(a,b));
                flag=1;
            }
        }
    }


    for(int i=0;i<PlayerNum;i++){
        for(int j=0;j<player[i].size();j++){
            if(player[i][j].first!=secretplayer[i][j].first||player[i][j].second!=secretplayer[i][j].second){
                ERR(1);
                file.close();
                secret.close();
                return 0;
            }
        }
    }
    //------------------------------------------------field
    for(int i=0;i<3;i++){
        int j=0;
        token.str("");
        token.clear();
        getline(file,line);
        token.str(line);
        while(token>>substring){
            field[i][j]=substring;
            j++;
        }
    }

    for(int i=0;i<3;i++){
        int j=0;
        stoken.str("");
        stoken.clear();
        getline(secret,sline);
        stoken.str(sline);
        while(stoken>>ssubstring){
            checkfield[i][j]=ssubstring/CODE-CODE2;
            j++;
        }
    }

     for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            if( field[i][j]!=checkfield[i][j]){
                ERR(1);
                file.close();
                secret.close();
                return 0;
            }
        }
     }
    //------------------------------------------------point
    for(int i=0;i<PlayerNum;i++){
        token.str("");
        token.clear();
        getline(file,line);
        token.str(line);
        while(token>>substring){
            total[i]=substring;
        }
    }

    for(int i=0;i<PlayerNum;i++){
        stoken.str("");
        stoken.clear();
        getline(secret,sline);
        stoken.str(sline);
        while(stoken>>ssubstring){
            checktotal[i]=ssubstring/CODE-CODE2;
        }
    }

    for(int i=0;i<PlayerNum;i++){
        if(total[i]!=checktotal[i]){
            ERR(1);
            file.close();
            secret.close();
            return 0;
        }
    }
    file.close();
    secret.close();
    //-----------------------------------------------------------------------------------
    cout<<"Card on the field :"<<endl;
    PrintField();
    if(!player[0].empty()){
        cout<<"Card that you have :"<<endl;
        PrintHuman();
    }
}

int Card::ERR(int a){
    if(a==1){
        cout<<"Data has already been destroyed!!!"<<endl;
        checkflag=1;
        return 1;
    }
}
