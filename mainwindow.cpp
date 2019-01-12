#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wid->hide();
    ui->adminPanel->hide();
    ui->categoryInput->addItem("master");
    ui->categoryInput->addItem("meddle");
    ui->categoryInput->addItem("beginer");
    QString dbName = QDir::currentPath()+"sportDB.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(db.open()){
        ui->dbStatue->setText("connect successfull");
        QSqlQuery q;
        if(!q.exec("CREATE TABLE IF NOT EXISTS sport(name text not null,"
                  " lName text not null, age int not null,"
                  "sport text not null, category text not null) ;" )){
            qDebug() << q.lastError().databaseText();
        }else{ /* table found and its works well */}
    }else {
        ui->dbStatue->setText("connect faild");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

// the clear button
void MainWindow::on_pushButton_2_clicked()
{
    ui->nameInput->clear();
    ui->lastnameInput->clear();
    ui->ageInput->clear();
    ui->sportInput->clear();
   }
// this is a save Button
void MainWindow::on_pushButton_clicked()
{
    //bool check;
    QSqlQueryModel *model = new QSqlQueryModel ;
    QSqlQuery q;
    QMessageBox mBox;
    QString nInput  = ui->nameInput->text();
    QString lnInput = ui->lastnameInput->text();
    QString aInput  = ui->ageInput->text();
    QString sInput  = ui->sportInput->text();
    QString cInput  = ui->categoryInput->currentText();
    if( !((nInput.isNull()||nInput.isEmpty())||(lnInput.isNull()||lnInput.isEmpty())
          ||(aInput.isNull()||aInput.isEmpty())||(sInput.isNull()||sInput.isEmpty())
          ||(cInput.isNull()||cInput.isEmpty())) ) {
        if(q.exec("INSERT INTO sport(name, lName,age,sport,category) "
                  "VALUES('"+nInput+"','"+lnInput+"','"+aInput+"','"+sInput+"','"+cInput+"');") ){
            ui->dbStatue->setText("saved");
            model->setQuery("select * from sport;");
            ui->res->setModel(model);
           /// for clearing the empty spacees
            ui->nameInput->clear();
            ui->lastnameInput->clear();
            ui->ageInput->clear();
            ui->sportInput->clear();


        }else{
            qDebug() << q.lastError().databaseText();
            ui->dbStatue->setText("falid to save");
        }
    }else{
        ui->dbStatue->setText("empty inputs...");
        mBox.critical(0,"empty","пожалуйста заполните свободные места");

    }

}

// when table showing button get clicked
void MainWindow::on_showingTable_clicked()
{
    //for deleteing and clear the data base
      QSqlQuery q ;
    if(q.exec("delete from sport where age = '25';")){
        ui->dbStatue->setText("deleted seccesfull...");
    }else{
        qDebug() << q.lastError().databaseText();
    }
    QSqlQueryModel *model = new QSqlQueryModel ;
    model->setQuery("select * from sport;");
    ui->res->setModel(model);
}

// when search button clicked
void MainWindow::on_searchButton_clicked()
{

    QSqlQueryModel *model = new QSqlQueryModel ;
    QString qry = "select * from sport " ;
    // s at the begining of the var name mean search
    QString sNameInput     = ui->searchNameInput->text();
    QString sLastNameInput = ui->searchLastNameInput->text();
    QString sAgeInput      = ui->searchAgeInput->text();
    QString sSportInput    = ui->searchSportInput->text();
    QString sCategoryInput = ui->searchCategoryInput->text();

//генератор для query
    QString *arr = new QString [5];
    bool checkForFirst = false;
        arr[0] = sNameInput;  arr[1] = sLastNameInput; arr[2] = sAgeInput;
        arr[3] = sSportInput; arr[4] = sCategoryInput;
        for(int i=0; i<5; i++){
            if( (arr[i].isEmpty() || arr[i].isNull()) ){
                continue;
            }else{
                if(checkForFirst){
                    qry = qry+" AND " ;
                }else{
                    qry = qry+" WHERE ";
                }
                if(i == 0){ qry = qry+" name LIKE '%"+sNameInput+"%' ";}
                else if(i == 1){ qry = qry+" lname LIKE '%"+sLastNameInput+"%' ";}
                else if(i == 2){ qry = qry+" age = "+sAgeInput+" ";}
                else if(i == 3){ qry = qry+" sport LIKE '%"+sSportInput+"%' ";}
                else if(i == 4){ qry = qry+" category LIKE '%"+sCategoryInput+"%' ";}
                else{}
                checkForFirst = true;
                }
            }
            qry = qry+" ;";
   /*   ///         ////        ///         ////        /////   */
            model->setQuery(qry);
            ui->dbStatue->setText("searching...");
            ui->res->setModel(model);
            delete [] arr ;
}

// login button in login wid
void MainWindow::on_loginButton_clicked()
{
    QString username = ui->loginName->text();
    QString password = ui->loginPassword->text();
    if(username == "admin" && password == "admin"){
        ui->wid->hide();
        ui->searchPanel->hide();
        ui->adminPanel->show();
    }else{
        QMessageBox messageBox;
        messageBox.critical(NULL,"Error","wrong username or password !");
        messageBox.setFixedSize(500,200);
    }

}
// login in admin menu
bool static showen = false;
void MainWindow::on_action_2_triggered()
{
    if(ui->adminPanel->isHidden()){
        if(showen){
            ui->wid->hide();
            ui->searchPanel->show();
        }else{
            ui->searchPanel->hide();
            ui->wid->show();
        }
        showen = !showen;
    }else{}
}
//logout in admin menu
void MainWindow::on_action_3_triggered()
{
    if(!ui->adminPanel->isHidden()){
        ui->adminPanel->hide();
        ui->searchPanel->show();
    }else{}
}
// change to english
void MainWindow::on_actionenglish_triggered()
{

}
// change to russian lang
void MainWindow::on_action_4_triggered()
{

}
