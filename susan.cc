//     susan.cc edge preserving noise reduction
//     Stephen Smith and Matthew Webster, FMRIB Image Analysis Group
//     Copyright (C) 1995-2006 University of Oxford
//     CCOPYRIGHT

#include "armawrap/newmat.h"
#include "newimage/newimageall.h"
#include "newimage/fmribmain.h"

using namespace NEWMAT;
using namespace NEWIMAGE;
using namespace std;

void print_usage(const string& progname) {
  cout << endl;
  cout << "Usage: susan <input> <bt> <dt> <dim> <use_median> <n_usans> [<usan1> <bt1> [<usan2> <bt2>]] <output>" << endl;
  cout << "<bt> is brightness threshold and should be greater than noise level and less than contrast of edges to be preserved." << endl;
  cout << "<dt> is spatial size (sigma, i.e., half-width) of smoothing, in mm." << endl;
  cout << "<dim> is dimensionality (2 or 3), depending on whether smoothing is to be within-plane (2) or fully 3D (3)." << endl;
  cout << "<use_median> determines whether to use a local median filter in the cases where single-point noise is detected (0 or 1)." << endl;
  cout << "<n_usans> determines whether the smoothing area (USAN) is to be found from secondary images (0, 1 or 2)." << endl;
  cout << "A negative value for any brightness threshold will auto-set the threshold at 10% of the robust range" << endl;
}


template <class T>
int fmrib_main(int argc, char *argv[])
{
  volume4D<T> input_vol,output_vol,usan_area;
  volume<T>   usan_vol[2];
  volume<float> kernel;
  float sigmabsq,sigmad,usan_sigmabsq[2]={0,0};
  bool  three_by_three=false,use_median=true;
  int   kernel_dim=2, num_usan=0;

  read_volume4D(input_vol,string(argv[1]));

  if (atof(argv[2]) < 0)  sigmabsq=pow((input_vol.robustmax()-input_vol.robustmin())/10.0,2.0); //do this for usans as well??
  else sigmabsq = atof(argv[2])*atof(argv[2]); //should multiply by 2 once compliance tests are complete
  sigmad = atof(argv[3]);
  kernel_dim=atoi(argv[4]);
  if (atoi(argv[5])==0) use_median=false;
  if (( sigmad/input_vol.xdim() < 0.01) || (sigmad/input_vol.ydim() <0.01) || (sigmad/input_vol.zdim()<0.01)) {three_by_three=true;}
  //set up kernel
  if (kernel_dim==3)
  {
    if (three_by_three) kernel = box_kernel(3,3,3);
    else kernel=gaussian_kernel3D(sigmad,input_vol.xdim(),input_vol.ydim(),input_vol.zdim(),2.0);
  }
  else
  {
    if (three_by_three) kernel = box_kernel(3,3,1);
    else kernel=gaussian_kernel3D(sigmad,input_vol.xdim(),input_vol.ydim(),0);
  }
  //kernel.value((kernel.xsize()-1)/2,(kernel.ysize()-1)/2,(kernel.zsize()-1)/2)=0;
  //Finalised kernel: Zero middle value
  //Set up external usans (if any)
  num_usan=atoi(argv[6]);
  if (num_usan>0)
  {
    read_volume(usan_vol[0],string(argv[7]));
    if (atof(argv[8]) < 0)  usan_sigmabsq[0]=pow((usan_vol[0].robustmax()-usan_vol[0].robustmin())/10.0,2.0);
    else  usan_sigmabsq[0] = atof(argv[8])*atof(argv[8]); //should multiply by 2 once compliance tests are complete
    usan_area=input_vol; //to set size
  }
  if (num_usan>1)
  {
    read_volume(usan_vol[1],string(argv[9]));
    if (atof(argv[10]) < 0)  usan_sigmabsq[1]=pow((usan_vol[1].robustmax()-usan_vol[1].robustmin())/10.0,2.0);
    else  usan_sigmabsq[1] = atof(argv[10])*atof(argv[10]); //should multiply by 2 once compliance tests are complete
  }
  //Process image
  output_vol=input_vol;
  for (int t=0;t<input_vol.tsize();t++)
  {
    if (num_usan==0) output_vol[t]=susan_convolve(input_vol[t],kernel,sigmabsq,use_median,num_usan);
    else {
      ShadowVolume<T> area(usan_area[t]);
      if (num_usan==1) output_vol[t]=susan_convolve(input_vol[t],kernel,sigmabsq,use_median,num_usan,&area,usan_vol[0],usan_sigmabsq[0]);
      if (num_usan==2) output_vol[t]=susan_convolve(input_vol[t],kernel,sigmabsq,use_median,num_usan,&area,usan_vol[0],usan_sigmabsq[0],usan_vol[1],usan_sigmabsq[1]);
    }
  }

  if (num_usan>0) save_volume4D(usan_area,(string(argv[argc-1])+"_usan_size"));
  save_volume4D(output_vol,string(argv[argc-1]));
  return 0;
}


int main(int argc,char *argv[])
{

  Tracer tr("main");

  string progname=argv[0];
  if (argc < 8)
  {
    print_usage(progname);
    return 1;
  }

  string iname=string(argv[1]);
  return call_fmrib_main(dtype(iname),argc,argv);
}
