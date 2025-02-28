# VaccineStorage_ASPEN
Vaccine Storage Project ASPEN

# Forking and Tracking via Git
clone the repository
`git remote -v` should output this:

`
origin  git@github.com:original-owner/repo-name.git (fetch)
origin  git@github.com:original-owner/repo-name.git (push)
`

create a fork on github and then run the following:
`git remote rename origin upstream`
`git remote add origin git@github.com:<your-username>/<repo-name>.git `

`git remote -v ` should now output something like this:

`origin    git@github.com:your-username/repo-name.git (fetch)
origin    git@github.com:your-username/repo-name.git (push)
upstream  git@github.com:original-owner/repo-name.git (fetch)
upstream  git@github.com:original-owner/repo-name.git (push)
`
