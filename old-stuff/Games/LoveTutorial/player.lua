Player = {}

function Player:load() -- loads variables for the player
    self.img = love.graphics.newImage("Assets/1.png")
    self.width = self.img:getWidth()
    self.height = self.img:getHeight()
    self.x = 50
    self.y = love.graphics.getHeight()/2 - self.height/2
    self.speed = 300
end

function Player:update(dt) -- checks the state of the game and changes it based off what has happened (pressing a keyboard, etc.), happens once per frame, dt = delta time, change in time
    self:move(dt)
    self:checkBoundaries()
end

function Player:move(dt) -- player can move up or down with W and S keys respectively
    if love.keyboard.isDown("w") then 
        self.y = self.y - self.speed * dt
    elseif love.keyboard.isDown("s") then
        self.y = self.y + self.speed * dt
    end
end

function Player:checkBoundaries() -- makes sure player can't move beyond the boundaries of the display
    if self.y < 0 then
        self.y = 0
    elseif self.y + self.height > love.graphics.getHeight() then
        self.y = love.graphics.getHeight() - self.height
    end
end

function Player:draw()
    love.graphics.draw(self.img, self.x, self.y)
end