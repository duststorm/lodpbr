/// Computes the roots of a cubic equation of the form ax^3 + bx^2 + cx + d = 0
/// http://www.worldserver.com/turk/opensource/
/// @param coeff Real coeffients (a, b, c, d)
/// @param roots Return values
/// @return 3 if all real roots, 1 if two imaginary roots and one real
int findCubicRoots(const double coeff[4], double roots[3])
{
  double a1, a2, a3;
//   a1 = coeff[2] / coeff[3];
//   a2 = coeff[1] / coeff[3];
//   a3 = coeff[0] / coeff[3];
  a1 = coeff[1] / coeff[0];
  a2 = coeff[2] / coeff[0];
  a3 = coeff[3] / coeff[0];

  double Q = (a1 * a1 - 3 * a2) / 9;
  double R = (2 * a1 * a1 * a1 - 9 * a1 * a2 + 27 * a3) / 54;
  double Qcubed = Q * Q * Q;
  double d = Qcubed - R * R;

  /* Three real roots */
  if (d >= 0) {
    double theta = acos(R / sqrt(Qcubed));
    double sqrtQ = sqrt(Q);
    roots[0] = -2 * sqrtQ * cos( theta           / 3) - a1 / 3;
    roots[1] = -2 * sqrtQ * cos((theta + 2 * PI) / 3) - a1 / 3;
    roots[2] = -2 * sqrtQ * cos((theta + 4 * PI) / 3) - a1 / 3;
    return (3);
  }

  /* One real root */
  else {
    double e = pow(sqrt(-d) + fabs(R), 1. / 3.);
    if (R > 0)
      e = -e;
    roots[0] = (e + Q / e) - a1 / 3.;
    return (1);
  }
}

/// Computes the roots of a cubic equation of the form ax^3 + bx^2 + cx + d = 0
/// http://www.glue.umd.edu/~nsw/ench250/cubiceq.htm
/// @param coeff Real coeffients (a, b, c, d)
/// @param roots Return values
/// @return 3 if all real roots, 1 if two imaginary roots and one real
int findCubicRoots2(const double coeff[4], double roots[3])
{
  double a = coeff[0], b = coeff[1], c = coeff[2], d = coeff[3];

  double p, q, D;

  //  Step 1: Calculate p and q
  p = (c/a) - ((b/a) * (b/a)) / 3.0;
  q = ( 2.0*pow((b/a), 3) - 9.0*b*c/a/a + 27*(d/a) ) / 27.0;
  // Step 2: Calculate discriminant D
  D = pow((p/3.0), 3) + pow((q/2.0), 2);
  // Step 3: Depending on the sign of D, you follow different strategy.
  // If D<0, three distinct real roots.
  // If D=0, three real roots of which at least two are equal.
  // If D>0, one real and two complex roots.
  // Step 3a: For D>0 and D=0
  // Calculate u and v
//   u = cubic_root(-q/2 + sqrt(D));
//     v = cubic_root(-q/2 - sqrt(D))
//     Find the three transformed roots
//     y1 = u + v
//     y2 = -(u+v)/2 + i (u-v)*sqrt(3)/2
//     y3 = -(u+v)/2 - i (u-v)*sqrt(3)/2
  // Step 3b: Alternately, for D<0, a trigonometric formulation is more convenient
  double phi = acos(-q/2.0/sqrt(pow(fabs(p), 3)/27.0));
  double y[3];
  y[0] =  2.0 * sqrt(fabs(p)/3.0) * cos(phi/3.0);
  y[1] = -2.0 * sqrt(fabs(p)/3.0) * cos((phi+PI)/3.0);
  y[2] = -2.0 * sqrt(fabs(p)/3.0) * cos((phi-PI)/3.0);
 
  // Step 4  Finally, find the three roots
  for (int i = 0; i < 3; ++i)
    roots[i] = y[i] - (b/a)/3.0;



  return 3;

}

/// Computes the roots of a cubic equation of the form ax^3 + bx^2 + cx + d = 0
/// Eigensystems for 3x3 Symmetric Matrices (Revisited), David Eberly, Geometric Tools Inc., 2006
/// @param A Given matrix
/// @param root Cubic roots of A
void findCubicRoots3 (double mat[9], double root[3])
{
  double A[3][3];
  A[0][0] = mat[0];
  A[0][1] = mat[1];
  A[0][2] = mat[2];
  A[1][0] = mat[3];
  A[1][1] = mat[4];
  A[1][2] = mat[5];
  A[2][0] = mat[6];
  A[2][1] = mat[7];
  A[2][2] = mat[8];

  double a00 = (double)A[0][0];
  double a01 = (double)A[0][1];
  double a02 = (double)A[0][2];
  double a11 = (double)A[1][1];
  double a12 = (double)A[1][2];
  double a22 = (double)A[2][2];
  double c0 = a00*a11*a22 + 2.0*a01*a02*a12 - a00*a12*a12 - a11*a02*a02 - a22*a01*a01;
  double c1 = a00*a11 - a01*a01 + a00*a22 - a02*a02 + a11*a22 - a12*a12;
  double c2 = a00 + a11 + a22;
  double c2Div3 = c2 * inv3;
  double aDiv3 = (c1 - c2*c2Div3)*inv3;
  if (aDiv3 > 0.0) { 
    aDiv3 = 0.0; }
  double mbDiv2 = 0.5*(c0 + c2Div3*(2.0*c2Div3*c2Div3 - c1));
  double q = mbDiv2*mbDiv2 + aDiv3*aDiv3*aDiv3;
  if (q > 0.0) { 
    q = 0.0; }
  double magnitude = sqrt(-aDiv3);
  double angle = atan2(sqrt(-q),mbDiv2)*inv3;
  double cs = cos(angle);
  double sn = sin(angle);
  root[0] = c2Div3 + 2.0*magnitude*cs;
  root[1] = c2Div3 - magnitude*(cs + root3*sn);
  root[2] = c2Div3 - magnitude*(cs - root3*sn);

  // Sort the roots here to obtain root[0] <= root[1] <= root[2].
}

/// Compute normals estimate from k-nearest neighbor for given point
/// @param p Given point
/// @return Normal vector
Vector computePointNormal (Point p) {

  vector<surfelListIter> k_nearest_neighbors;

  int comps;
  int k = k_nearest;
  k_nearest_neighbors = kdTree->kNearestNeighbors (p, k, comps);

  // average neighbor position
  double pos[3] = {0.0, 0.0, 0.0};

  for (int i = 0; i < k; ++i) {
    pos[0] += k_nearest_neighbors[i]->position().x();
    pos[1] += k_nearest_neighbors[i]->position().y();
    pos[2] += k_nearest_neighbors[i]->position().z();
  }
  Point avg (pos[0] / k, pos[1] / k, pos[2] / k);

  // compute covariance matrix
  double cov_matrix[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  
  for (int i = 0; i < k; ++i) {
    Vector dif = k_nearest_neighbors[i]->position() - avg;
    cov_matrix[0] += dif.x() * dif.x();
    cov_matrix[1] += dif.x() * dif.y();
    cov_matrix[2] += dif.x() * dif.z();
    cov_matrix[3] += dif.y() * dif.x();
    cov_matrix[4] += dif.y() * dif.y();
    cov_matrix[5] += dif.y() * dif.z();
    cov_matrix[6] += dif.z() * dif.x();
    cov_matrix[7] += dif.z() * dif.y();
    cov_matrix[8] += dif.z() * dif.z();
  }

  // characteristic polynomial
  // ax^3 + bx^2 + cx + d = 0  (a,b,c,d are real coeficientss)

//   double a, b, c, d;
//   a = -1;
//   b = cov_matrix[0] + cov_matrix[4] + cov_matrix[8];
//   c = cov_matrix[5]*cov_matrix[7] + cov_matrix[1]*cov_matrix[3] + cov_matrix[2]*cov_matrix[6] -
//     cov_matrix[0]*cov_matrix[4] - cov_matrix[0]*cov_matrix[8] - cov_matrix[4]*cov_matrix[8];
//   d = cov_matrix[0] * (cov_matrix[4]*cov_matrix[8] - cov_matrix[5]*cov_matrix[7]) -
//     cov_matrix[1] * (cov_matrix[3]*cov_matrix[8] - cov_matrix[5]*cov_matrix[6]) +
//     cov_matrix[2] * (cov_matrix[3]*cov_matrix[7] - cov_matrix[4]*cov_matrix[6]);

  // find roots of cubic equation

  double root[3] = {0.0, 0.0, 0.0};
  findCubicRoots3 (cov_matrix, root);

  // Get min eigenvalue
  double minEigenvalue = root[0];
  if (root[1] < minEigenvalue)
    minEigenvalue = root[1];
  if (root[2] < minEigenvalue)
    minEigenvalue = root[2];

  // compute eigenvector associated with minEigenvalue
  
  Vector r (cov_matrix[0] - minEigenvalue, cov_matrix[1], cov_matrix[2]);
  Vector t (cov_matrix[3], cov_matrix[4] - minEigenvalue, cov_matrix[5]);
  //  Vector u (cov_matrix[6], cov_matrix[7], cov_matrix[8] - minEigenvalue);

  Vector eigenvector = CGAL::cross_product(r, t);
  double len = sqrt(eigenvector[0]*eigenvector[0] + eigenvector[1]*eigenvector[1] + eigenvector[2]*eigenvector[2]);

  // Return normalized eigenvector (normal)
  return eigenvector/len;

}

/// Compute the edge cost between two neighbors surfels for the minimum spanning tree
/// @param s0 First surfel iterator
/// @param s1 Second surfel iterator
/// @return Edge cost
double edgeCost (surfelListIter s0, surfelListIter s1) {
  // edge cost = 1 - | n0 dot n1 |
  // Hughes Hoppe Master Thesis - pp 26
  double dot = s0->normal() * s1->normal();
  return 1.0 - fabs(dot);
}

/// Compute the normals orientation for each point in model
/// See 'Surface Reconstruction from Unorganized Points'
/// Hughes Hoppe, PhD Thesis, 1995, pages 24-27
void computeNormalsOrientation (void) {

  int k = k_nearest;

  // typedefs for minimum spanning tree
  // a node of the spanning tree contains two surfels and the edge
  // cost between them, ordered increasingly by lowest edge cost
  typedef pair <surfelListIter, surfelListIter> surfelPair;
  typedef pair <double, surfelPair> spanningTreeNode;
  multimap < double, surfelPair, std::less <double> > outside;
  multimap < double, surfelPair, std::less <double> >::iterator outside_it;
  vector< surfelListIter > k_nearest_neighbors;

  cout << "initializing checked vector" << endl;

  // vector of flags determining surfel has had its normal checked already
  // initialize all surfels with false
  bool checked [surfels.size()];

  int max = surfels.size();
  for (int j = 0; j < max; ++j) {
    if (j % 1000 == 0)
      cout << j << " / " << surfels.size() << " checked" << endl;
    checked[j] = 0;
  }

  cout << "Finding first point" << endl;

  int cnt = 0;
  // Find point with largest z coordinate
  surfelListIter cur = surfels.begin();
  for (surfelListIter it = surfels.begin(); it != surfels.end(); ++it) {

    ++cnt;
    if (cnt%1000 == 0)
      cout << cnt << " / " << surfels.size() << " far z" << endl;

    if (it->position().z() > cur->position().z())
      cur = it;
  }

  // Make sure the normal of maximum z surfel is pointing towards +z
  //  if (cur->normal() * Vector (0.0, 0.0, 1.0) < 0.0)
  if (cur->normal().z() < 0.0)
    ((Surfel*)&(*cur))->setNormal( cur->normal()*-1.0 );
  checked[cur->id()] = 1;

  double edge_cost;
  // Insert edges incident on first node
  k_nearest_neighbors = kdTree->kNearestNeighbors (cur->position(), k);
  for (unsigned int i = 0; i < k_nearest_neighbors.size(); ++i) {
    edge_cost = edgeCost (cur, k_nearest_neighbors[i]);
    outside.insert (spanningTreeNode (edge_cost, surfelPair(cur, k_nearest_neighbors[i])));
  }
  
  surfelListIter prev = cur;
  cout << "Spanning tree traversal" << endl;

  cnt = 0;

  // Greedy algorithm to compute minimum spanning tree until outside list is empty
  while (!outside.empty()) {
    ++cnt;
    if (cnt%1000 == 0) {
      cout << cnt << " / " << surfels.size() << " " << outside.size() << endl;
      outside_it = outside.begin();
      for (int j = 0; j < 10; ++j) {
	cout << " , " << outside_it->first;
	outside_it++;
      }
      cout << endl;
    }

    // Edge with smallest cost on candidate edges set
    surfelPair curPair = outside.begin()->second;
    // First-second node of map, lowest edge cost
    cur = curPair.second;
    prev = curPair.first;

    // Remove edge from candidate set
    outside.erase ( outside.begin() );

    // If the normal of this surfel has already been checked, skip to next edge
    if (!checked[cur->id()]) {

      // Check normal orientation of current surfel with originated surfel of minimum spanning tree
      if (prev->normal() * cur->normal() < 0.0)
	((Surfel*)&(*cur))->setNormal( cur->normal() * -1.0 );
      checked[cur->id()] = 1;

      // Insert edges incindent on current surfel on candidate edges set
      k_nearest_neighbors = kdTree->kNearestNeighbors (cur->position(), k);
      for (int i = k_nearest_neighbors.size() - 1; i >= 0 ; --i) {
	edge_cost = edgeCost (cur, k_nearest_neighbors[i]);
	outside.insert (spanningTreeNode (edge_cost, surfelPair(cur, k_nearest_neighbors[i])));
      }
    }
  }
}


/// Compute normal estimate for all points
void computeNormals (void) {
  int i = 0;
  for (surfelListIter it = surfels.begin(); it != surfels.end(); ++it) {
    Vector n = computePointNormal (it->position());
    ((Surfel*)&(*it))->setNormal( n );
    ++i;
    if (i%1000 == 0)
      cout << i << " / " << surfels.size() << endl;
  }
}