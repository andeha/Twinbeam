/*  Simd-none.hpp | sometime-still passing two 64-bit 'words'. */

extern double n₋sqrtᵥ₂(double x, double n); /* ⬷ see --<sqrt-simd-0.cpp> for details. */

MACRO simd_tᵦ simd_initᵦ(double c) { return 𝛽₋simd { .doubles={c,c} }.𝟷𝟸𝟾bit; } 
MACRO simd_tᵦ __builtin_simd_addᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ a₂.doubles[0]+b₂.doubles[0], a₂.doubles[1]+    
  b₂.doubles[1] } }; return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_subᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ a₂.doubles[0]-b₂.doubles[0], a₂.doubles[1]-    
  b₂.doubles[1] } }; return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_mulᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ a₂.doubles[0]*b₂.doubles[0], a₂.doubles[1]*    
  b₂.doubles[1] } }; return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_divᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ a₂.doubles[0]/b₂.doubles[0], a₂.doubles[1]/    
  b₂.doubles[1] } }; return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_rcpᵦ(simd_tᵦ x) { 𝛽₋simd x₂ {.𝟷𝟸𝟾bit=x}, y {       
  .doubles={ 1/x₂.doubles[0], 1/x₂.doubles[1] } }; return y.𝟷𝟸𝟾bit; }           
MACRO simd_tᵦ __builtin_simd_sqrtᵦ(simd_tᵦ x) { 𝛽₋simd x₂ {.𝟷𝟸𝟾bit=x}, y {      
  .doubles={ n₋sqrtᵥ₂(x₂.doubles[0],2), n₋sqrtᵥ₂(x₂.doubles[1],2) } };         
  return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_rsqrtᵦ(simd_tᵦ x) { 𝛽₋simd x₂ {.𝟷𝟸𝟾bit=x}, y {     
 .doubles={ 1/n₋sqrtᵥ₂(x₂.doubles[0],2), 1/n₋sqrtᵥ₂(x₂.doubles[1],2) } };      
 return y.𝟷𝟸𝟾bit; }
MACRO simd_tᵦ __builtin_simd_fmaddᵦ(simd_tᵦ a, simd_tᵦ b, simd_tᵦ c) { 𝛽₋simd  
  a₂ {.𝟷𝟸𝟾bit=a}, b₂={.𝟷𝟸𝟾bit=b}, c₂={.𝟷𝟸𝟾bit=c}, y { .doubles={ a₂.doubles[0]+ 
  (b₂.doubles[0]*c₂.doubles[0]), a₂.doubles[1]+(b₂.doubles[1]*c₂.doubles[1])   
  } }; return y.𝟷𝟸𝟾bit; } /* ⬷ Mips-flavored 'fused multiply and add'. */     
MACRO simd_tᵦ __builtin_simd_minᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ min(a₂.doubles[0],b₂.doubles[0]), min(         
  a₂.doubles[1],b₂.doubles[1]) } }; return y.𝟷𝟸𝟾bit; }                          
MACRO simd_tᵦ __builtin_simd_maxᵦ(simd_tᵦ a, simd_tᵦ b) { 𝛽₋simd a₂ {.𝟷𝟸𝟾bit=a},
  b₂={.𝟷𝟸𝟾bit=b}, y { .doubles={ max(a₂.doubles[0],b₂.doubles[0]), max(         
  a₂.doubles[1],b₂.doubles[1]) } }; return y.𝟷𝟸𝟾bit;
}


