class ItemsToCollect : public StaticObject  
{  
public:  
   ItemsToCollect(sf::Vector2f position); // Updated constructor to match the argument list in Bullets.cpp  
   ~ItemsToCollect() = default;  

   virtual void collide(GameObject& otherObject) override;  
   virtual void enemyCollide(Enemy& otherObject) override;  
   virtual void playerCollide(Player& otherObject) override;  
   virtual void explosionCollide(Explosion& otherobject) override;  
};