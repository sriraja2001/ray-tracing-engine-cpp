#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include<memory>
#include<vector>
#include "core/hittable.h"

class hittable_list : public hittable {
  public:
    hittable_list();
    hittable_list(shared_ptr<hittable> object) {
      add(object);
    }

    void add(shared_ptr<hittable> object) {
      objects.push_back(object);
    }

    void clear() {
      objects.clear();
    }

    bool hit(const ray &r, const double ray_tmin, const double ray_tmax, hit_record &rec) {
      hit_record temp_rec;
      bool hit_anything = false;
      double closest = ray_tmax;

      for(shared_ptr<hittable> obj: objects) {
        if(obj->hit(r, ray_tmin, closest, temp_rec)) {
          hit_anything = true;
          rec = temp_rec;
          closest = temp_rec->t; 
        }
      }

      return hit_anything;
    }

  private:
    vector<shared_ptr<hittable>> objects;
}

#endif
