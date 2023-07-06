

#include <QFile>
#include <QTextStream>
#include <QString>

QFile ifile("index.txt");
QFile sifile("secindex.txt");
QFile efile("employee.txt");
int ind=0,sind=0,i;
QString data;
class employee{
public :QString id,name,dept,pro,city,salary,phone;
public: int add(QString id,QString name,QString dept,QString pro,QString city,QString salary,QString phone);
    int search(QString fid);
    QStringList recdisp(int p);
    QStringList ssearch(QString fname);
    QStringList rems(QString skey);
    int remove(QString rid);
    int mod(QString id,QString name,QString dept,QString pro,QString city,QString salary,QString phone,int addr);

};
employee sss;
class index{
public: QString id,addr;
public: void write();
    int init();

}in[100],in1;


class sindex{
public: QString sid,sname;
public: void swrite();
    void sinit();

}si[100],sin1;


void index::write(){
    ifile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&ifile);
    for(i=0;i<ind;i++)
        out<<in[i].id<<"|"<<in[i].addr<<"\n";
    ifile.flush();
    ifile.close();
}


void sindex::swrite(){
    sifile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&sifile);
    for(i=0;i<sind;i++)
        out<<si[i].sname<<"|"<<si[i].sid<<"\n";
    sifile.flush();
    sifile.close();
}


int index::init()
{
    if(!ifile.open(QIODevice::ReadOnly | QIODevice::Text)){
		ind = 0;
        return 0;
	}
     QTextStream inf(&ifile);
	for (ind = 0;; ind++)
	{

		QString line = inf.readLine();
        if(line.isNull())
            break;
        QStringList part=line.split("|");
        in[ind].id=part[0];
        in[ind].addr=part[1];


	}
    ifile.close();
    return ind;
}


void sindex::sinit()
{
    if(!sifile.open(QIODevice::ReadOnly | QIODevice::Text)){
        sind = 0;
        return;
    }
     QTextStream inf(&sifile);
    for (sind = 0;; sind++)
    {


        QString line = inf.readLine();
        if(line.isNull())
            break;
        QStringList part=line.split("|");
        si[sind].sid=part[1];
        si[sind].sname=part[0];

    }

    sifile.close();
}

int employee::search(QString fid)
{
	int low = 0, high = ind - 1, mid;
	while (low <= high)
	{
        mid = (low + high) / 2;
        if ((fid.compare(in[mid].id)) == 0)
			return mid;
        else if ((fid.compare(in[mid].id)) > 0)
			low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

QStringList employee::recdisp(int p)
{
    efile.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream inf(&efile);
    efile.seek(in[p].addr.toLongLong());
    QStringList part=inf.readLine().split("|");
    efile.close();
    return part;
}




int employee::add(QString id, QString name, QString dept, QString pro, QString city, QString salary, QString phone){

    if(sss.search(id)!=-1){
        return -1;
    }
    efile.open(QIODevice::Append| QIODevice::Text);
     QTextStream outd(&efile);
    efile.seek(efile.size());


     for(i=ind;i>0;i--){
        if(id.compare(in[i-1].id)<0)
            in[i]=in[i-1];
        else break;
    }
     in[i].id=id;
     in[i].addr=QString::number(efile.pos());
     ind++;

     for(i=sind;i>0;i--){
        if(name.compare(si[i-1].sname)<0)
            si[i]=si[i-1];
        else if(name.compare(si[i-1].sname)==0 && id.compare(si[i-1].sid)<0)
            si[i]=si[i-1];
        else break;
     }
     si[i].sid=id;
     si[i].sname=name;
     sind++;

    outd<<id+"|"+name+"|"+dept+"|"+pro+"|"+city+"|"+salary+"|"+phone+"\n";
     efile.flush();
     efile.close();
    in1.write();
    sin1.swrite();
     return 1;

}

QStringList employee::ssearch(QString fname)
{
	
    QStringList li;
    sifile.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream inf(&sifile);
	for(int j=0;j<sind;j++)
		if(fname.compare(si[j].sname)==0)
				{
                    li.append(si[j].sid);
				}
    sifile.close();
    return li;
}

QStringList employee::rems(QString skey)
{
	QStringList list;
	for (i = 0; i < sind; i++)
		if (skey.compare(si[i].sname) == 0)
			list.append(si[i].sid);
	return list;
}

int employee::remove(QString rid){
    int spos,pos;
	for (i = 0; i < sind; i++)
		if (rid.compare(si[i].sid) == 0)
		{
			spos = i;
			break;
		}

    pos = sss.search(rid);
    if(pos==-1){
        return -1;
    }
    efile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream inf(&sifile);
    efile.seek(in[pos].addr.toLongLong());
    efile.write("$",1);
	for (i = pos; i < ind; i++)
		in[i] = in[i + 1];
	ind--;
	for (i = spos; i < sind; i++)
		si[i] = si[i + 1];
	sind--;
    in1.write();
    sin1.swrite();
    efile.close();
	return 1;
}












