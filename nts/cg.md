## Introduction to Computational Geometry

### Main Points
Computational geometry involves solving geometric problems using efficient algorithms and data structures. CGAL (Computational Geometry Algorithms Library) provides powerful tools to work with geometric objects and operations.

Key concepts include:
1. **Kernels**:
   - Kernels define types and operations for geometric primitives.
   - CGAL provides three primary kernels:
     - **Epic**: CGAL::Exact_predicates_inexact_constructions_kernel
     - **Epec**: CGAL::Exact_predicates_exact_constructions_kernel
     - **Sqrt**: CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt
   - Use the cheapest kernel that satisfies the requirements:
     - **Epic**: Best for predicates, faster but inexact for constructions.
     - **Epec**: Exact for constructions but does not support square roots.
     - **Sqrt**: Exact with square roots but slower.

2. **Predicates vs Constructions**:
   - Predicates: Boolean results from operations (e.g., "Do two segments intersect?").
   - Constructions: Operations producing geometric objects (e.g., "Construct a line passing through two points").

3. **Field Types (K::FT)**:
   - Epic kernel uses double, where constructions may be inexact.
   - Epec kernel uses special types that guarantee exactness without square roots.
   - Sqrt kernel handles constructions with square roots.

4. **Additional Points**:
   - Use int for 32-bit integers and long for 64-bit integers.
   - Use double for floating-point numbers.
   - Use CGAL::Gmpz for arbitrary precision integer and CGAL::Gmpq for arbitrary precision rational (increasing precision and cost).