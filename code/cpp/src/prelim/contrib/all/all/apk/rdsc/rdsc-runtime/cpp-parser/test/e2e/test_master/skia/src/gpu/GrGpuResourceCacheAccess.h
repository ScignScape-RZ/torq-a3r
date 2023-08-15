/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrGpuResourceCacheAccess_DEFINED
#  define GrGpuResourceCacheAccess_DEFINED
#  include "include/gpu/GrGpuResource.h"
#  include "src/gpu/GrGpuResourcePriv.h"
namespace skiatest
{
  class Reporter;
}
/**
 * This class allows GrResourceCache increased privileged access to GrGpuResource objects.
 */
class GrGpuResource::CacheAccess
{
private:
    /** The cache is allowed to go from no refs to 1 ref. */
  void ref()
  {
    fResource->addInitialRef();
  }
    /**
     * Is the resource currently cached as scratch? This means it is cached, has a valid scratch
     * key, and does not have a unique key.
     */
  bool isScratch() const
  {
    return !fResource->getUniqueKey().isValid() && fResource->fScratchKey.isValid() && GrBudgetedType::kBudgeted == fResource->resourcePriv().budgetedType();
  }
    /**
     * Called by the cache to delete the resource under normal circumstances.
     */
  void release()
  {
    fResource->release();
    if (!fResource->hasRef())
    {
      delete fResource;
    }
  }
    /**
     * Called by the cache to delete the resource when the backend 3D context is no longer valid.
     */
  void abandon()
  {
    fResource->abandon();
    if (!fResource->hasRef())
    {
      delete fResource;
    }
  }
    /** Called by the cache to assign a new unique key. */
  void setUniqueKey(const GrUniqueKey& key)
  {
    fResource->fUniqueKey = key;
  }
    /** Is the resource ref'ed */
  bool hasRef() const
  {
    return fResource->hasRef();
  }
    /** Called by the cache to make the unique key invalid. */
  void removeUniqueKey()
  {
    fResource->fUniqueKey.reset();
  }
  uint32_t timestamp() const
  {
    return fResource->fTimestamp;
  }
  void setTimestamp(uint32_t ts)
  {
    fResource->fTimestamp = ts;
  }
  void setTimeWhenResourceBecomePurgeable()
  {
    SkASSERT(fResource->isPurgeable());
    fResource->fTimeWhenBecamePurgeable = GrStdSteadyClock::now();
  }
    /**
     * Called by the cache to determine whether this resource should be purged based on the length
     * of time it has been available for purging.
     */
  GrStdSteadyClock::time_point timeWhenResourceBecamePurgeable()
  {
    SkASSERT(fResource->isPurgeable());
    return fResource->fTimeWhenBecamePurgeable;
  }
  int* accessCacheIndex() const
  {
    return &fResource->fCacheArrayIndex;
  }
  CacheAccess(GrGpuResource* resource)
    : fResource(resource)
  {
  }
  CacheAccess(const CacheAccess& that)
    : fResource(that.fResource)
  {
  }
  CacheAccess& operator=(const CacheAccess&);
    // No taking addresses of this type.
  const CacheAccess* operator&() const;
  CacheAccess* operator&();
  GrGpuResource* fResource;
  friend class GrGpuResource;
  friend class GrResourceCache;
  friend void test_unbudgeted_to_scratch(skiatest::Reporter* reporter);
};
inline GrGpuResource::CacheAccess GrGpuResource::cacheAccess()
{
  return CacheAccess(this);
}
inline const GrGpuResource::CacheAccess GrGpuResource::cacheAccess() const
{
  return CacheAccess(const_cast<GrGpuResource*>(this));
}
#endif
