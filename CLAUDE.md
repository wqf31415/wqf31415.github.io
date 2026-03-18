# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a personal blog built with [Hexo](https://hexo.io/), a static site generator. The repository uses branch structure:
- `source` branch: Contains blog source files (markdown posts, configurations, theme) - this is the current branch
- `master` branch: Contains generated static HTML files deployed to GitHub Pages

## Commands

All commands use `npx hexo` or npm scripts:

```bash
# Install dependencies
npm install

# Clone the Next theme (required after fresh install)
git clone https://github.com/next-theme/hexo-theme-next themes/next
# Copy theme configuration from backup
cp themes_config/next/_config.yml themes/next/

# Clean generated files
npm run clean
# or
npx hexo clean

# Generate static site
npm run build
# or
npx hexo generate

# Start local dev server at http://localhost:4000
npm run server
# or
npx hexo server

# Deploy to GitHub Pages (master branch)
npm run deploy
# or
npx hexo deploy

# Create a new post
npx hexo new "Post Title"
```

## Project Structure

- `_config.yml` - Main Hexo configuration
- `_config.next.yml` - Next theme configuration overrides
- `source/` - Source content
  - `source/_posts/` - Blog posts (markdown format)
  - `source/_drafts/` - Unpublished drafts
  - `source/uploads/` - Image uploads
- `themes/next/` - Next theme (git submodule)
- `themes_config/` - Backup of custom theme configuration and language patches
- `public/` - Generated static files (generated, not checked in)
- `scaffolds/` - Post templates
- `package.json` - Dependencies and scripts

## Key Configuration

- Theme: Next 8.25.0 (configured in `_config.yml` and `themes_config/`)
- Syntax highlighting: highlight.js with mermaid exclusion (mermaid handled by plugin)
- Markdown rendering: hexo-renderer-markdown-it-plus
- Deployment: git to master branch on GitHub
- mermaid diagram support enabled via hexo-filter-mermaid-diagrams

## Blog Content

Blog posts are written in Markdown and located in `source/_posts/`. Drafts are in `source/_drafts/`.
