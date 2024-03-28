AI = {}

function AI:load()
    self.img = love.graphics.newImage("assets/2.png")
    self.width = self.img:getWidth()
    self.height = self.img:getHeight()
    self.x = love.graphics.getWidth() - 50 - self.width
    self.y = love.graphics.getHeight()/2 - self.height/2
    self.yVel = 0
    self.speed = 300

    self.timer = 0
    self.rate = 0.25
end

function AI:update(dt)
    AI:move(dt)
    AI:checkBoundaries()
    self.timer = self.timer + dt
    if self.timer > self.rate then
        self.timer = 0
        AI:acquireTarget()
    end
end

function AI:move(dt)
    self.y = self.y + self.yVel * dt
end

function AI: acquireTarget()
    if Ball.y > self.y + self.height then
        self.yVel = self.speed
    elseif Ball.y + Ball.height < self.y then
        self.yVel = -self.speed
    else
        self.yVel = 0
    end
end

function AI:checkBoundaries()
    if self.y < 0 then
        self.y = 0
    elseif self.y + self.height > love.graphics.getHeight() then
        self.y = love.graphics.getHeight() - self.height
    end
end

function AI:draw()
    love.graphics.draw(self.img, self.x, self.y)
end