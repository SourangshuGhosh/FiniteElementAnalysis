*** This is an input file for tesing

[mesh]
  type=asfem
  dim=2
  xmin= 0.0
  xmax=10.0
  ymin= 0.0
  ymax=10.0
  nx=250
  ny=250
  meshtype=quad4
[end]

[dofs]
name=C Mu
[end]


[elmts]
  [ch2d]
	  type=cahnhilliard
	  dofs=C Mu
	  mate=free
    domain=alldomain
  [end]
[end]

[mates]
  [free]
    type=cahnhilliard
    params=1.0 2.5 0.06  2          0.1    0.9
    //     D   Chi Kappa MateChoice Calpha Cbeta
  [end]
[end]

[ics]
  [rand]
    type=random
    dof=C
    params=0.45 0.55
  [end]
[end]

[timestepping]
  type=be
  dt=1.0e-5
  dtmax=5.0e-1
  opts=5
  endtime=1.0e2
  adaptive=true
[end]

[job]
  type=transient
  debug=dep
  interval=2
[end]
