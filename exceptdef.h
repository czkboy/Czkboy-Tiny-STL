#ifndef __LMSTL_EXCEPTDEF_H__
#define __LMSTL_EXCEPTDEF_H__

namespace lmstl {

#define __THROW_RUNTIME_ERROR(expr, what) if((expr)) throw std::runtime_error(what);
#define __THROW_OUT_OF_RANGE_ERROR(expr, what) if((expr)) throw std::out_of_range(what);
#define __THROW_BAD_ALLOC__ std::cerr<<"Out of Memory"<<std::endl; exit(1)

}
#endif // !__LMSTL_EXCEPTDEF_H__
