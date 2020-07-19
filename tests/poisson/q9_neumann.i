*** This is an input file for tesing

[mesh]
  type=asfem
  dim=2
  xmin=0.0
  xmax=10.0
  ymin=0.0
  ymax=10.0
  nx=100
  ny=100
  meshtype=quad9
[end]

[dofs]
name=phi
[end]

[elmts]
    [poisson]
	  type=poisson
	  dofs=phi
	  mate=linear
      domain=alldomain
    [end]
[end]

[mates]
  [linear]
    type=constpoisson
    params=1.0e1 0.3
  [end]
[end]



[bcs]
  [fixphi]
    type=dirichlet
    dof=phi
    boundary=left
    value=0.0
  [end]
  [flux]
    type=neumann
    dof=phi
    boundary=right
    value=-2.5
  [end]
[end]

[job]
  type=static
  debug=dep
[end]
