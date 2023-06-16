#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include<QPalette>

employee s;
employee d[100];
index ind1;
sindex sind1;
int lnum,ccount;
QString buff;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   lnum=ind1.init();
    sind1.sinit();
    ui->setupUi(this);
    ui->g_btn->setHidden(true);
    ui->listWidget->setHidden(true);
    ui->g_btn_2->setHidden(true);
    ui->mlw->setHidden(true);
    ui->lcdNumber->display(lnum);
    ui->lcdNumber->show();

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{   if(   ui->tb1->text().trimmed()==""||
        ui->tb2->text().trimmed()==""||
        ui->tb3->text().trimmed()==""||
        ui->tb4->text().trimmed()==""||
        ui->tb5->text().trimmed()==""||
        ui->tb6->text().trimmed()==""||
        ui->tb7->text().trimmed()==""){
        QMessageBox::warning(nullptr, "Warning", "Enter all details!");
        return;
    }
   int a= s.add(ui->tb1->text(),ui->tb2->text(),ui->tb3->text(),ui->tb4->text(),ui->tb5->text(),ui->tb6->text(),ui->tb7->text());
   if(a==-1){
        QMessageBox::warning(nullptr, "Warning", "Employee ID already exists!");
       return;

    }
   QMessageBox::information(nullptr, "Success", "Employee Added!");
   ui->tb1->setText("");
    ui->tb2->setText("");
   ui->tb3->setText("");
    ui->tb4->setText("");
   ui->tb5->setText("");
    ui->tb6->setText("");
   ui->tb7->setText("");
    ui->lcdNumber->display(++lnum);
   ui->lcdNumber->show();
}


void MainWindow::on_sbi_btn_clicked()
{
   ui->sbn->setText("");
   if(ui->sbi->text().trimmed()==""){
       QMessageBox::warning(nullptr, "Warning", "Enter ID!");
       return;
   }


   int p=(search(ui->sbi->text()));
   if(p==-1){
       QMessageBox::information(nullptr, "Information", "No Record Found!");
       return;
   }
   QStringList list=s.recdisp(p);
   ui->tableWidget->setRowCount(1);

   for(int k=0;k<7;k++){
       QTableWidgetItem* item=new QTableWidgetItem(list.at(k));
       item->setTextAlignment(Qt::AlignCenter);
       ui->tableWidget->setItem(0,k,item);
   }

}


void MainWindow::on_sbn_btn_clicked()
{
   ui->sbi->setText("");

   if(ui->sbn->text().trimmed()==""){
       QMessageBox::warning(nullptr, "Warning", "Enter Name!");
       return;
   }


   QStringList list=s.ssearch(ui->sbn->text());
   if(list.size()==0){
       QMessageBox::information(nullptr, "Information", "No Record Found!");
       return;
   }
    ui->tableWidget->setRowCount(0);
   for ( i = 0; i < list.size(); i++) {
       QString it = list.at(i);
       int p=search(it);
       QStringList data=s.recdisp(p);
      int rc= ui->tableWidget->rowCount();
       ui->tableWidget->setRowCount(rc+1);
       for(int k=0;k<7;k++){
           QTableWidgetItem* item=new QTableWidgetItem(data.at(k));
           item->setTextAlignment(Qt::AlignCenter);
           ui->tableWidget->setItem(i,k,item);
       }
   }

}



void MainWindow::on_rbn_btn_clicked()
{

   ui->rbi->setText("");
   if(ui->rbn->text().trimmed()==""){
       QMessageBox::warning(nullptr, "Warning", "Enter Name!");
       return;
   }

   QStringList list=s.rems(ui->rbn->text());
   if(list.size()==0){
       QMessageBox::information(nullptr, "Information", "No Record Found!");
       return;
   }
   ui->rtable->setHidden(true);
   ui->r_btn->setHidden(true);
   ui->g_btn->setHidden(false);
   ui->listWidget->setHidden(false);
   QListWidgetItem* h=new QListWidgetItem("Select ID to be removed");
   QFont font = h->font();
   font.setBold(true);
   h->setFont(font);
   h->setFlags(Qt::NoItemFlags);  // Disable selection and interaction
   ui->listWidget->addItem(h);
   for (const QString& text : list) {
       QListWidgetItem* item = new QListWidgetItem(text);
       item->setFlags(item->flags() | Qt::ItemIsSelectable);
       ui->listWidget->addItem(item);
   }


}


void MainWindow::on_g_btn_clicked()
{

   QListWidgetItem* item= ui->listWidget->currentItem();
   if (item== nullptr)
   {
       QMessageBox::warning(nullptr, "Warning", "Select an ID!");
       return;
   }
   ui->g_btn->setHidden(true);
   ui->listWidget->setHidden(true);

   ui->rtable->setHidden(false);
   ui->r_btn->setHidden(false);

    QString rid = item->text();
   int p=search(rid);
   QStringList list=s.recdisp(p);
   ui->rtable->setRowCount(1);

   for(int k=0;k<7;k++){
       QTableWidgetItem* item=new QTableWidgetItem(list.at(k));
       item->setTextAlignment(Qt::AlignCenter);
       ui->rtable->setItem(0,k,item);
    ui->listWidget->clear();
}
}


void MainWindow::on_r_btn_clicked()
{

        if (ui->rtable->rowCount()==0)
        {
               QMessageBox::warning(nullptr, "Warning", "No Record selected!");
               return;
        }
       QString key=ui->rtable->item(0,0)->text();
       if (key == "")
       {
           QMessageBox::warning(nullptr, "Warning", "No Record selected!");
           return;
       }
       QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question", "Do you want to proceed?", QMessageBox::Yes | QMessageBox::No);
       if (reply == QMessageBox::No)
       {
           return;
       }
       s.remove(key);
       QMessageBox::information(nullptr, "Success", "Record deleted!");
       ui->rtable->setRowCount(0);
       ui->rbn->setText("");
       ui->rbi->setText("");
       ui->lcdNumber->display(--lnum);
       ui->lcdNumber->show();
}


void MainWindow::on_rbi_btn_clicked()
{
       int p=search(ui->rbi->text());
       if(p==-1){
           QMessageBox::warning(nullptr, "Not found", "No record found");
           return;
       }
       QStringList list=s.recdisp(p);
       ui->rtable->setRowCount(1);

       for(int k=0;k<7;k++){
           QTableWidgetItem* item=new QTableWidgetItem(list.at(k));
           item->setTextAlignment(Qt::AlignCenter);
           ui->rtable->setItem(0,k,item);

}
}


void MainWindow::on_mbn_btn_clicked()
{
    ui->mid->setText("");

    if(ui->mbn->text().trimmed()==""){
               QMessageBox::warning(nullptr, "Warning", "Enter Name!");
               return;
    }

    QStringList list=s.rems(ui->mbn->text());
    if(list.size()==0){
               QMessageBox::information(nullptr, "Information", "No Record Found!");
               return;
    }
    ui->mtable->setHidden(true);
    ui->r_btn_2->setHidden(true);
    ui->g_btn_2->setHidden(false);
    ui->mlw->setHidden(false);
    QListWidgetItem* h=new QListWidgetItem("Select ID to be modified");
    QFont font = h->font();
    font.setBold(true);
    h->setFont(font);
    h->setFlags(Qt::NoItemFlags);  // Disable selection and interaction
    ui->mlw->addItem(h);
    ui->mlw->setWindowTitle("Select ID");
    ui->mlw->addItems(list);

}


void MainWindow::on_g_btn_2_clicked()
{
    QListWidgetItem* item= ui->mlw->currentItem();
    if (item== nullptr)
    {
               QMessageBox::warning(nullptr, "Warning", "Select an ID by clicking it!");
               return;
    }
    ui->g_btn_2->setHidden(true);
    ui->mlw->setHidden(true);

    ui->mtable->setHidden(false);
    ui->r_btn_2->setHidden(false);

    QString rid = item->text();
    int p=search(rid);
    QStringList list=s.recdisp(p);
    ui->mtable->setRowCount(1);

    for(int k=0;k<7;k++){
               QTableWidgetItem* item=new QTableWidgetItem(list.at(k));
               item->setTextAlignment(Qt::AlignCenter);
               ui->mtable->setItem(0,k,item);
}
    ui->mlw->clear();
    QString key=ui->mtable->item(0,0)->text();
    s.remove(key);
    QFile file("employee.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QTextStream in(&file);
               i=0;
               while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList fields = line.split("|");
           if(!(fields[0][0]=='$')){

               d[i].id=fields[0];
               d[i].name=fields[1];
               d[i].dept=fields[2];
               d[i].pro=fields[3];
               d[i].city=fields[4];
               d[i].salary=fields[5];
               d[i].phone=fields[6];
               i++;
               ccount++;
           }
               }
               ui->label_13->setText(d[0].id+d[0].name+d[1].id+d[1].name);
               file.close();

    }
}


void MainWindow::on_r_btn_2_clicked()
{
    if (ui->mtable->rowCount()==0)
    {
                   QMessageBox::warning(nullptr, "Warning", "No Record selected!");
                   return;
    }
    QString key=ui->mtable->item(0,0)->text();
    if (key == "")
    {
                   QMessageBox::warning(nullptr, "Warning", "No Record selected!");
                   return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question", "Do you want to proceed?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
    {
                   return;
    }
    QFile::remove("employee.txt");
    QFile::remove("index.txt");
    QFile::remove("secindex.txt");
    int lnum=ind1.init();
    sind1.sinit();


    for(int z=0;z<ccount;z++){
                   s.add(d[z].id,d[z].name,d[z].dept,d[z].pro,d[z].city,d[z].salary,d[z].phone);
                   lnum++;

    }
    s.add(ui->mtable->item(0,0)->text(),ui->mtable->item(0,1)->text(),ui->mtable->item(0,2)->text(),ui->mtable->item(0,3)->text(),ui->mtable->item(0,4)->text(),ui->mtable->item(0,5)->text(),ui->mtable->item(0,6)->text());
    lnum++;
    ui->lcdNumber->display(lnum);
    ui->lcdNumber->show();
    QMessageBox::information(nullptr, "Success", "Record modified!");
    ui->mtable->setRowCount(0);
    ui->mbn->setText("");
    ui->mid->setText("");
    ccount=0;


}



void MainWindow::on_mid_btn_clicked()
{
    int p=search(ui->mid->text());
    if(p==-1){
                   QMessageBox::warning(nullptr, "Not found", "No record found");
                   return;
    }
    ui->mtable->setRowCount(1);
    QStringList list=s.recdisp(p);

    for(int k=0;k<7;k++){
                   QTableWidgetItem* item=new QTableWidgetItem(list.at(k));
                   item->setTextAlignment(Qt::AlignCenter);
                   ui->mtable->setItem(0,k,item);
}
    ui->mlw->clear();
    QString key=ui->mtable->item(0,0)->text();
    s.remove(key);
    QFile file("employee.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                   QTextStream in(&file);
                   i=0;
                   while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList fields = line.split("|");
           if(!(fields[0][0]=='$')){

               d[i].id=fields[0];
               d[i].name=fields[1];
               d[i].dept=fields[2];
               d[i].pro=fields[3];
               d[i].city=fields[4];
               d[i].salary=fields[5];
               d[i].phone=fields[6];
               i++;
               ccount++;
           }
                   }
                   ui->label_13->setText(d[0].id+d[0].name+d[1].id+d[1].name);
                   file.close();

}
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->sbi->setText("");
    ui->sbn->setText("");
    ui->rbi->setText("");
    ui->rbn->setText("");
    ui->mid->setText("");
    ui->mbn->setText("");
    ui->mtable->setRowCount(0);
    ui->rtable->setRowCount(0);
    ui->g_btn->setHidden(true);
    ui->listWidget->setHidden(true);
    ui->g_btn_2->setHidden(true);
    ui->mlw->setHidden(true);
    ui->tableWidget_2->setRowCount(0);
    if (index == 4) {
                   QTableWidget* tableWidget = ui->tableWidget_2;
                   if (tableWidget != nullptr) {
           QFile file("employee.txt");
           if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QTextStream in(&file);
               int row = 0;
               while (!in.atEnd()) {
                   QString line = in.readLine();

                   QStringList fields = line.split('|');

                   if (row >= tableWidget->rowCount()) {
                       tableWidget->insertRow(row);
                   }
                   if(fields[0][0]=='$'){
                       QTableWidgetItem* item = new QTableWidgetItem("Deleted record");
                       item->setTextAlignment(Qt::AlignCenter);
                       tableWidget->setSpan(row,0,1,7);
                       tableWidget->setItem(row, 0, item);
                   }
                   else{

                   for (int col = 0; col < fields.size(); ++col) {
                       QTableWidgetItem* item = new QTableWidgetItem(fields[col]);
                       item->setTextAlignment(Qt::AlignCenter);
                       tableWidget->setItem(row, col, item);
                   }
                   }

                   ++row;
               }

               file.close();
           }
                   }
    }

}





