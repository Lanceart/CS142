#include<thread>
#include<cilk/cilk.h>
#include<cilk/cilk_api.h>
double reduce(double * ansp,size_t n){

        if(n<10000)
        {
                double ans = 0;
                for(size_t i=0;i<n;i++)
                        ans += ansp[i];
                return ans;
        }
        double L,R;
        L = cilk_spawn  reduce(ansp,n/2);
        R = reduce(ansp + n/2,n-n/2);
        cilk_sync;
        return L + R;

}


template <typename Func>
double integral(Func& f, size_t n, double low, double high) {
        n /=10;
        double ans = 0.0;
        double* ansp = new double [n];
        double dx = (high-low)/n;
        //double dx10 = dx*10;
        //double ansp[1000] = {0};
        /****
        Fill in your code here
        ****/
        n = n/100;

        cilk_for(size_t i=0;i<n;i++)
        {
                double sum = 0;
                for(size_t j = 0;j<100;j++)
                {
                double x = low + dx*(i*100+j);
                //sum += f(x);
                if(j%2==0)sum+=2.0*f(x);
                else
                        sum+=4.0*f(x);
                }

                ansp[i] = sum;
        }
        ans += f(high);
        ans -= f(low);
        ans += reduce(ansp,n);
        //for(size_t i=0;i<n;i++)
        //ans+=ansp[i];
        //std::cout<<n<<" "<<low<<" " << high<<std::endl;
        return ans/6/(n*100/2);
}
