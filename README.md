# SDS Distributed Key-Value
sdsdkv is a configurable distributed key-value service.

## Building
sdsdkv depends on several pieces of software infrastructure, so it is convenient
to build these dependencies using spack. If spack is already configured in your
environment, then please skip to **Install dependencies**. Please note that a
bash-like environment is assumed herein.

### Get spack.

```
git clone https://github.com/spack/spack.git
```

### Configure spack and build environment.

```
source spack/share/spack/setup-env.sh
# Setup spack for modules support.
spack bootstrap
```

### Install dependencies.

```
# Checkout sds-repo
git clone https://xgitlab.cels.anl.gov/sds/sds-repo.git
# Add to spack.
spack repo add sds-repo
# Install via spack.
spack install --dirty sdskeyval+leveldb
spack install --dirty ssg+mpi
spack install --dirty ch-placement
# Refresh spack environment.
source spack/share/spack/setup-env.sh
# Load required modules.
#spack load -r autoconf
#spack load -r automake
#spack load -r libtool
source <(spack module tcl loads --dependencies sdskeyval ssg ch-placement autoconf automake libtool)
```

### Get and build sdsdkv.

```
git clone https://xgitlab.cels.anl.gov/sds/sdsdkv.git
cd sdsdkv && autoreconf --force --install && ./configure CXX=mpic++ && make
```
