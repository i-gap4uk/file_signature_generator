#ifndef FS_GEN_IMPL_H
#define FS_GEN_IMPL_H

namespace fs_generator{
class IFSGenImpl{
public:
    virtual void generate_file_signature() = 0;
    virtual void abort_generation() = 0;
};
}

#endif // FS_GEN_IMPL_H
