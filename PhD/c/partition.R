  sam=function(n,p,k){
    if(p==1) cat(k,n,"\n") else {
    for(i in (n-p+1):1){
      k2=c(k,i)
      sam((n-i),(p-1),k2)
    }}
  }

  sam(50,10,{})
