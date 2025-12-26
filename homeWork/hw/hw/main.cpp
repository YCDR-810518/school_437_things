#include<stdio.h>
int main(){
    long long N,sum_bit=0,count_bit=0;
    scanf("%lld",&N);
    while(N!=0){
        sum_bit+=N%10;
        N=N/10;
        count_bit++;
    }
    printf("%lld %lld",sum_bit,count_bit);
}
/*
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int sumPerson;            //人数
    int sumPre,typePre;//总数，种类数，每种的件数
    cin>>sumPerson>>typePre;
    //输入各种礼品的概率
    //i行j列表示第i人选择第j中小礼品的概率
    vector<vector<double>>chanIndex[sumPerson][typePre];
    vector<int> numPre[typePre];
    for(int i = 0; i<typePre; i++)
    {
        cin >> numPre[i];
    }
    //输入各个人选择各个小礼品的概率
    for(int i=0; i<sumPerson; i++)
    {
        for(int j=0; j<typePre; j++)
        {
            cin>>chanIndex[i][j];
        }
    }
    
    int BLP=0;//最喜欢的礼物
    int PIH=0;//拿到最喜欢的礼物的人数
    double BLPC=chanIndex[0][0];//选择最喜欢的礼物的概率
    double BLPC2 = chanIndex[0][0];
    int BLP2 = 0;
    int BLPP=0;//拿到自己最喜欢的礼物的人数
    for(int i=0; i<sumPerson; i++)
    {
        for(int j=0;j<typePre;j++)
        {
            if(chanIndex[i][j]>BLPC)
            {
                BLPC=chanIndex[i][j];
                BLP=j;
            }
        }
        for(int j=0;j<typePre;j++)
        {
            if(chanIndex[i][j]>BLPC2 && BLPC2<BLPC)
            {
                BLPC2=chanIndex[i][j];
                BLP2 =j;
            }
        }
        
    }
    if(numPre[BLP]!=0)
    {
        numPre[BLP]--;
        PIH++;
    }
    else
    {
        numPre[BLP2]--;
    }
    cout<<PIH;
}
*/
/*
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
int main(){
    int n;    //待测试系统个数
    cin >> n;
    cin.ignore();//忽略换行符
    
    vector<vector<int>> timeAndWater(n);   //每行一个系统
    vector<vector<int>> money(n);
    vector<double> speeds(n);
    vector<double>totalMoneys(n,0.0);
    //int firstTime = 1;
    //int num;
    string line;
    double maxSpeed,minSpeed;//最快，最慢系统
    double maxMoney,minMoney;//最多，最少处理费用

    //读取数据（按行）
    for(int i=0; i<n; i++)
    {
        getline(cin, line);    //直接读取一整行
        stringstream ss(line);

        bool readingWater = true;
        int num;
        while(ss>>num)
        {
            if(num == -1)
            {
                readingWater = !readingWater;
                continue;
            }
            if(readingWater)
                timeAndWater[i].push_back(num);
            else
                money[i].push_back(num);
        }
        //下面进行数据处理
        //将时间转换为秒进行处理
        if(timeAndWater[i].size()>=2)
        {
            
            //计算开始时间的秒数
            int secS = timeAndWater[i][0]%100;
            int minuteS = ((timeAndWater[i][0]/100)%100)*60;
            int hourS = (timeAndWater[i][0]/10000)*3600;
            int sumSecS = secS+minuteS+hourS;//总时间（开始）

            //计算结束时间的秒数
            int secE = timeAndWater[i][1]%100;
            int minuteE = ((timeAndWater[i][1]/100)%100)*60;
            int hourE = (timeAndWater[i][1]/10000)*3600;
            int sumSecE = secE+minuteE+hourE;//结束的总时间

            //时间差
            int timeDiff;
            if(sumSecE>sumSecS)
                timeDiff = sumSecE-sumSecS;
            if(sumSecE<sumSecS)
                timeDiff = (24*3600)+sumSecE-sumSecS;
            
            //总用水量
            int totalWater = 0;
            for(int j = 2; j<timeAndWater[i].size(); j++)
            {
                totalWater += timeAndWater[i][j];
            }

            //计算速度
            speeds[i] = (timeDiff>0)? (double)(totalWater)/timeDiff:0;

            //计算总费用
            //每个净水设施的费用
            for(int j : money[i])
            {
                totalMoneys[i]+=j;
            }
            if(totalWater>0)
                totalMoneys[i]/=totalWater;
        }
    }
        //下面是输出程序
        maxSpeed=speeds[0];
        minSpeed=speeds[0];
        maxMoney=totalMoneys[0];
        minMoney=totalMoneys[0];
        int caculate[4] = {1,1,1,1};
        for(int i=1; i<n; i++)
        {
            //找出最大和最小速度
            if(maxSpeed<speeds[i])
            {
                maxSpeed=speeds[i];
                caculate[0] = i+1;    //指定处理最快的系统
            }
            if(minSpeed>speeds[i])
            {
                minSpeed = speeds[i];
                caculate[1] = i+1;
            }

            //找出最大和最小费用
            if(minMoney>totalMoneys[i])
            {
                minMoney = totalMoneys[i];
                caculate[2] = i+1;
            }
            if(maxMoney<totalMoneys[i])
            {
                maxMoney = totalMoneys[i];
                caculate[3] = i+1;
            }
            
        }

        //下面统一输出
        cout<<"System No."<< caculate[0] <<" is fastest: "<< setiosflags(ios::fixed) <<
            setprecision(6)<< maxSpeed << " t/s" <<'\n';
        cout<<"System No."<< caculate[1] <<" is slowest: "<< setiosflags(ios::fixed) <<
            setprecision(6)<< minSpeed << " t/s" <<'\n';
        cout<<"System No."<< caculate[2] << " is cheapest: "<< setiosflags(ios::fixed) <<
            setprecision(2)<< minMoney << " yuan/t" <<'\n';
        cout<<"System No."<< caculate[3] << " is costliest: "<< setiosflags(ios::fixed) <<
            setprecision(2)<< maxMoney << " yuan/t" <<endl;
    return 0;
}
*/
/*
#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n=3, m;
    cin >> n >> m;    //获取人数和喜好
    vector<vector<int>> like(n,vector<int>(m));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> like[i][j];    //用vector向量数组自动识别录入数据
        }
    }
    
    //处理数据
    for(int i=0; i<m; i++)    //第0人拿a号书
    {
        if(like[0][i]==0)continue;//不喜欢就跳过
        
            for(int j = 0; j<m; j++)
            {
                if(j==i)continue;
                if(like[1][j]==0)continue;
                
                
                    for(int k = 0; k<m; k++)
                    {
                        if(k==i||k==j)continue;
                        if(like[2][k]==0)continue;
                        
                        cout << '('<<i+1<<','<<j+1<<','<<k+1<<')'<<endl;
                    }
                
            }

            
        
    }
    
    
}
 */

/*
int main()
{   //Add your code here
   int m;int n;int s;
    int temp=0;
    scanf("%d",&m);
    n=0;
    s=0;
   while (1) {
       
       temp=n+1;
       n++;
       s+=temp;
      if (s>=m) {
         break;
      }
   }



 


   printf("m=%d,n=%d,s=%d", m, n, s);
}
 */
/*
int excNumBit(int a,int excBit);
int main()
{
    int a;
    int b;
    long int c;
    cin >> a >> b;
    //add your code here
   int a_123 = excNumBit(a,3);
   int b_123 = excNumBit(b,3);
   if (a_123!=0 && b_123!=0) {
        c = a_123 * 1000 +b_123;
    }else {
        c = a_123+b_123;
    }

    printf("a=%d,b=%d,c=%ld\n", a, b, c);
}
*/

/*
@spam 要包含<string>，只能在C++下运行
@int a 传入一个数字（至少两位）
@int excBit 标志要转换的位数（从右向左）
@return 返回已经转换的位数
*/

/*
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{  //add your code here
    int a,b;
    string a1;
    scanf("%d",&a);
    a1 = to_string(a);
    vector<char>A_arr;
    for(const char c :a1){
        A_arr.push_back(c);
    }
    reverse(A_arr.begin(),A_arr.end());
    for (int i=0; i < A_arr.size(); i++) {
        a1[i] = A_arr[i];
    }
    b = stoi(a1);
    printf("a=%d, b=%d\n", a, b);
}
*/
