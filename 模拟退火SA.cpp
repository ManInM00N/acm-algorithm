struct Point
{
    int num;
    double a[50];
    Point(){};
    Point(int num):num(num){}
    Point operator- (const Point &B)
    {
        Point res(num);
        for (int i = 0; i < num; i++)
        {
            res.a[i]=a[i]-B.a[i];
        }
        return res;
    }
    double dis( Point B)
    {
        double sum =0;
        for (int i = 0; i < num; i++)
        {
            sum+=(a[i]-B.a[i])*(a[i]-B.a[i]);
        }
        return sqrt(sum);
    }
};
Point p[MAXN];
Point SA(Point &start){
    Point delta(start.num);
    double T = 10000.0;
    double ans = 1e20;
    
    while (T>=eps)
    {
        double ave=0;
        Point dis(start.num); //num维空间下的最小球覆盖
        for (int i = 0; i < n; i++)
        {
            dis.a[i] = start.dis(p[i]);
            ave+=dis.a[i];
        }
        ave/=n;
        for (int i = 0; i < start.num; i++)
        {
            delta.a[i] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < start.num; j++)
            {
                delta.a[j]+=(dis.a[i]-ave)*(p[i].a[j]-start.a[j])/ave;
            }
        }
        for (int i = 0; i < start.num; i++)
        {
            start.a[i]+=(delta.a[i])*T;
        }
        T*=0.99999;
    }
    return start;
}