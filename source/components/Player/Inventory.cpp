//
// Joe Gamble - 21/04/2020
//

#include <gamelib/Player/Inventory.h>
#include <utility>

Inventory::Inventory(RenderData* _RD, const Vector3& pos, int _row, float slot_size) : row(_row)
{
  max_size = bag.getBagStats()->max_level * row;

  slots.reserve(max_size);
  Vector3 slot_pos = pos;
  for (int i = 1; i <= max_size; i++)
  {
    bool unlocked = false;

    if (i < bag.getBagStats()->bag_size)
    {
      unlocked = true;
    }

    Slot new_slot = Slot(slot_pos, i, unlocked);
    slots.emplace_back(new_slot);

    if (i % row == 0)
    {
      slot_pos.x = pos.x;
      slot_pos.y += slot_size;
    }
    else
    {
      slot_pos.x += slot_size;
    }
  }
  bag = Bag(this, _row, _RD);
}

void Inventory::updateSlots(int _size)
{
  for (int i = 0; i < _size; i++)
  {
    Slot* slot = &slots.at(i);
    if (!slot->getSlotStats()->unlocked)
    {
      slot->getSlotStats()->unlocked = true;
      slot->spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITESMOKE);
    }
  }
}

void Inventory::setBagLevel(int _level)
{
  getBag()->getBagStats()->bag_level = _level;
  getBag()->getBagStats()->bag_size  = row * _level;
  updateSlots(getBag()->getBagStats()->bag_size);
}

void Inventory::addItem(std::reference_wrapper<SceneObject> object)
{
  int unlocked_slots = bag.getBagStats()->bag_size;

  for (int i = 0; i < unlocked_slots; i++)
  {
    auto* slot = getSlot(i);

    if (!slot->getSlotStats()->occupied)
    {
      bag.getContents()->addNewObject(object.get());
      slot->setItem(dynamic_cast<ItemReference*>(&bag.getContents()->getObjects()->back().get()));
      return;
    }
  }
}

void Inventory::Slot::setItem(ItemReference* _item)
{
  ref = _item;

  ref->setPos(item_anchor);
  ref->setSize({spriteComponent()->getSprite()->width() - (slotStats.slot_offset * 2),
                spriteComponent()->getSprite()->height() - (slotStats.slot_offset * 2)});
  getSlotStats()->occupied = true;
}

Inventory::Bag::Bag(Inventory* inv, int row, RenderData* _RD) : this_inventory(inv), contents(_RD)
{
  getContents()->getObjects()->reserve(bagStats.max_level * row);
  getBagStats()->bag_level = 1;
  getBagStats()->bag_size  = row;
}

Item* Inventory::Bag::getItem(int item_id)
{
  auto* item = dynamic_cast<Item*>(&getContents()->getObjects()->at(item_id).get());
  return item;
}

Inventory::Slot* Inventory::getSlot(int slot_id)
{
  return &slots.at(slot_id);
}

Inventory::Slot::Slot(Vector3& _pos, int _id, bool _unlocked) :
  pos(std::move(_pos)),
  item_anchor({pos.x + slotStats.slot_offset, pos.y + slotStats.slot_offset, 0})
{
  getSlotStats()->slot_id  = _id;
  getSlotStats()->unlocked = _unlocked;
}
