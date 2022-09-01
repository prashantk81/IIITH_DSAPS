#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//******************** Rows and Columns Removal**************************
void remove_column(int ***rgb,int *seam_path,int H,int W){
    for(int i=0;i<H;i++){
        int x=seam_path[i];
        for(int j=x;j<W-1;j++){
            for(int k=0;k<3;k++){
                 rgb[i][j][k]=rgb[i][j+1][k];
            }
        }
        rgb[i][W-1][0]=-1;
        rgb[i][W-1][0]=-1;
        rgb[i][W-1][0]=-1;

    }
}

//******************** finding seam **************************************
void find_seam(int ***rgb,float **cost,int H,int W){
    int seam_path[H];
    int min=cost[H-1][0];
    int k=0,z=H-1;
    for(int i=1;i<W;i++){
        if(cost[H-1][i]<min){
            min=cost[H-1][i];
            k=i;
        }
    }
    seam_path[z--]=k;
    for(int i=H-1;i>0;i--){
        if(k==0){
            if(cost[i-1][k]>cost[i-1][k+1]){k=k+1;}
        }
        else if(k==W-1){
            if(cost[i-1][k]>cost[i-1][k-1]){k=k-1;}
        }
        else{
            if(cost[i-1][k]<cost[i-1][k+1]){
                if(cost[i-1][k]>cost[i-1][k-1]){k=k-1;}
            }
            else{
                if(cost[i-1][k-1]>cost[i-1][k+1]){k=k+1;}
                else{k=k-1;}
            }
        }
        seam_path[z--]=k;
    }
    remove_column(rgb,seam_path,H,W);
}

//***************************finding cost matrix*****************************
void find_cost_matrix(int ***rgb,float **dual_grad,int H,int W){
    float **cost_mat;
    cost_mat=new float *[H];
    cost_mat[0] = new float[W];
    for(int i=0;i<W;i++){
        cost_mat[0][i]=dual_grad[0][i];
    }
    for(int i=1;i<H;i++){   
        cost_mat[i] = new float[W];
        for(int j=0;j<W;j++){
            if(j==0){
                cost_mat[i][j]=dual_grad[i][j]+min(cost_mat[i-1][j],cost_mat[i-1][j+1]);
            }
            else if(j==W-1){
                cost_mat[i][j]=dual_grad[i][j]+min(cost_mat[i-1][j],cost_mat[i-1][j-1]);
            }
            else{
                cost_mat[i][j]=dual_grad[i][j]+min(min(cost_mat[i-1][j],cost_mat[i-1][j+1]),cost_mat[i-1][j-1]);
            }
        }
    }
    find_seam(rgb,cost_mat,H,W);
}

//*****************Energy Matrix Calculations*****************
void seam_carving(int ***rgb, int H, int W, int C){
    float **dual_grad; 
    dual_grad=new float *[H];              
    for(int i=0;i<H;i++){
        dual_grad[i] = new float[W];
        for(int j=0;j<W;j++){
            int val1=0;
            int val2=0;
            for(int k=0;k<3;k++){
                int x=rgb[i][(j+W-1)%W][k]-rgb[i][(j+1)%W][k];
                x=x*x;
                val1+=x;
            }
            for(int k=0;k<3;k++){
                int x=rgb[(i+H-1)%H][j][k]-rgb[(i+1)%H][j][k];
                x=x*x;
                val2+=x;
            }
            float res=sqrt(val1+val2);
            dual_grad[i][j]=res; 
        }                   
    }
    find_cost_matrix(rgb,dual_grad,H,W);  
}

//*************************SOLVE function*********************** 
void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) {
    seam_carving(rgb, H, W,C);
}

//**********************transpose matrix***********************
int *** transpose_rgb(int ***rgb, int H, int W,int C){
	int ***rgb_new;
	rgb_new=new int **[W];	
	for(int i=0;i<W;i++){
		rgb_new[i]=new int *[H];
		for(int j=0;j<H;j++){
			rgb_new[i][j]=new int [C];
			for(int k=0;k<3;k++){
				rgb_new[i][j][k]=rgb[j][i][k];
			}
		}
	}
	return rgb_new;
}

//************************MAIN function***********************
int main() {
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();
    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;
	 while(W_< W){
        solve(rgb, H, W, C, H_, W_, C_);
        W--;
    }
	while(H_<H){
		int ***transpose_mat=transpose_rgb(rgb, H, W, C);
		solve(transpose_mat, W, H, C, H_, W_, C_);
		rgb=transpose_rgb(transpose_mat,W,H,C);
        H--;
	}
    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}
