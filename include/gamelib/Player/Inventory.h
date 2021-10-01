//
// Joe Gamble 21/04/20
//

#ifndef MYNETGAME_INVENTORY_H
#define MYNETGAME_INVENTORY_H

#include <gamelib/ObjectPooler.h>
#include <vector>

enum ItemType
{
  DEFAULT  = -1,
  WEAPON   = 0,
  UTILITY  = 1,
  TREASURE = 2
};

class Item : public InteractableObject
{
 public:
  struct ItemStats
  {
    ItemType itemType = DEFAULT;
    int range         = 1.0F;
    int price         = 25.0F;
  };
  Item()  = default;
  ~Item() = default;
  ItemStats* getItemStats() { return &itemStats; }

 protected:
  ItemStats itemStats;
};

class Inventory
{
 public:
  Inventory() = default;
  Inventory(RenderData* _RD, const Vector3& pos, int row, float slot_size);
  ~Inventory() = default;
  // something

  struct Slot : public GameObject
  {
   public:
    struct SlotStats
    {
      int slot_id       = 0;
      bool selected     = false;
      bool unlocked     = false;
      bool highlighted  = false;
      bool occupied     = false;
      float slot_offset = 7.5F;
    };

    // test
    Slot(Vector3& pos, int _id, bool _unlocked);
    ~Slot() = default;

    ItemReference* getRef() { return ref; }
    void setItem(ItemReference* item);
    Vector3& getSlotPos() { return pos; }
    Rect getSlotZone() { return spriteComponent()->getBoundingBox(); }
    SlotStats* getSlotStats() { return &slotStats; }

   private:
    ItemReference* ref = nullptr;
    SlotStats slotStats;
    Vector3 pos;
    Vector3 item_anchor = {0, 0, 0};
  };

  struct Bag
  {
   public:
    struct BagStats
    {
      int max_level = 3;
      int bag_level = 0;
      int bag_size  = 0;
    };

    Bag() = default;
    Bag(Inventory* inv, int row, RenderData* _RD);
    ~Bag() = default;

    ObjectPool* getContents() { return &contents; }
    Item* getItem(int item_id);
    BagStats* getBagStats() { return &bagStats; }

   private:
    BagStats bagStats;
    ObjectPool contents;
    Inventory* this_inventory = nullptr;
  };

  Bag* getBag() { return &bag; }
  void setBagLevel(int _level);
  std::vector<Inventory::Slot>* getSlots() { return &slots; }
  Slot* getSlot(int slot_id);
  void updateSlots(int _size);
  void addItem(std::reference_wrapper<SceneObject> object);

 private:
  Bag bag;
  std::vector<Slot> slots;

  int max_size = 0;
  int row      = 0;
};

#endif  // MYNETGAME_INVENTORY_H
