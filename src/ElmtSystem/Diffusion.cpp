//****************************************************************
//* This file is part of the AsFem framework
//* A Simple Finite Element Method program (AsFem)
//* All rights reserved, Yang Bai @ CopyRight 2020
//* https://github.com/yangbai90/AsFem.git
//* Licensed under GNU GPLv3, please see LICENSE for details
//* https://www.gnu.org/licenses/gpl-3.0.en.html
//****************************************************************

#include "ElmtSystem/ElmtSystem.h"

void ElmtSystem::Diffusion(const int &isw,const int &nDim,const int &nNodes,
            const double &t,const double &dt,const double (&ctan)[2],
            const Vector3d &gpCoord,
            const vector<double> &gpU,const vector<double> &gpV,
            const vector<Vector3d> &gpGradU,const vector<Vector3d> &gpGradV,
            const ShapeFun &shp,
            const vector<double> &ScalarMaterials,
            const vector<Vector3d> &VectorMaterials,
            const vector<RankTwoTensor> &Rank2Materials,
            const vector<RankFourTensor> &Rank4Materials,
            vector<double> &Hist,const vector<double> &HistOld,vector<double> &Proj,
            MatrixXd &K,VectorXd &rhs){
    if(nDim){};
    if(VectorMaterials.size()) {}
    if(Rank2Materials.size()){}
    if(Rank4Materials.size()){}
    
    // In constpoisson material:
    // ScalarMaterials[0]=1.0;// Diffusivity
    // ScalarMaterials[1]=0.0;// dD/dc
    if(isw==3||isw==6){
        for(int i=1;i<=nNodes;++i){
            rhs(i)+=gpV[0]*shp.shape_value(i)
                   +ScalarMaterials[0]*(gpGradU[0]*shp.shape_grad(i));
            if(isw==6){
                for(int j=1;j<=nNodes;++j){
                    K(i,j)+=shp.shape_value(j)*shp.shape_value(i)*ctan[1]
                           +ScalarMaterials[1]*shp.shape_value(j)*(gpGradU[0]*shp.shape_grad(i))*ctan[0]
                           +ScalarMaterials[0]*(shp.shape_grad(j)*shp.shape_grad(i))*ctan[0];
                }
            }
        }
    }
    else if(isw==4){
        // init history variable
        fill(Hist.begin(),Hist.end(),0.0);
    }
    else if(isw==8){
        // update hist
        Hist=HistOld;
    }
    else if(isw==9){
        // do projection
        Proj[0]=ScalarMaterials[0]*gpGradU[0](1);
        Proj[1]=ScalarMaterials[0]*gpGradU[0](2);
        Proj[2]=ScalarMaterials[0]*gpGradU[0](3);
        Proj[3]=gpU[0];
        Proj[4]=t*dt;
        Proj[5]=gpCoord(1);
        Proj[6]=gpV[0];
        Proj[7]=gpGradV[0](1);
    }
}