#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

class LoadBalancer{
  private:
    //thread pool
  
    LoadBalancer();
    ~LoadBalancer();
  public:
    static LoadBalancer Create();

};

#endif //_LOAD_BALANCER_H_